/*
 *
 * Filename: set_motor_output.c
 * Authors: Michele Furci, Dario Mengoli
 *
 * Description:
 * Demone che si occupa di applicare l'output ai motori prelevandolo
 * direttamente dal topic uORB motor_output
 *
 * NOTE:
 * prima di avviarlo e' necessario eseguire
 *		uorb start
 * in piu', vanno caricati i driver per l'output pwm:
 * nel caso di PX4FMU (pin servo on-board):
 *		fmu mode_pwm
 * nel caso di PX4IO:
 *		px4io start
 *
 */

#include <nuttx/config.h>
#include <nuttx/sched.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/mount.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <stdbool.h>

#include <stdbool.h>
#include <uORB/uORB.h>
#include <uORB/topics/motor_output.h>
#include <uORB/topics/unibo_vehicle_status.h>
#include <uORB/topics/safety.h>
#include <uORB/topics/esc_status.h>

#include <nuttx/i2c.h>
#include <nuttx/mtd.h>
#include <nuttx/fs/nxffs.h>
#include <nuttx/fs/ioctl.h>

#include <drivers/drv_pwm_output.h>

#define MIN_PWM 1000
#define MAX_PWM 2100
#define PWM_DISARMED 0
#define PWM_ARMED 900
#define PWM_PREFLIGHT 1100
#define MIN_RPM 0
#define MAX_RPM 8500  //TODO should be taken from configuration file dinamically changing with voltage
#define RPM_MODE 1       //set to zero if pwm is used, rpm mode otherwise

#if !defined(ATECH) && !defined(IRIS)
	#error "You must define ATECH or IRIS macros"
#endif

// numero di motori effettivamente collegati
/*#ifdef ATECH
	#define MOTORS_START 4   //TODO should be taken from configuration file
	#define MOTORS_NUMBER 8	//TODO should be taken from configuration file
#endif
#ifdef IRIS
	#define MOTORS_START 0	//TODO should be taken from configuration file
	#define MOTORS_NUMBER 4	//TODO should be taken from configuration file
#endif*/
#define MOTORS_START 0	//TODO should be taken from configuration file
#define MOTORS_NUMBER 4	//TODO should be taken from configuration file

/* Deamon libraries? */
#include <systemlib/systemlib.h>
#include <systemlib/err.h>
// globali per thread
static bool unibomo_thread_should_exit = false;
static bool unibomo_thread_running = false;
static int unibomo_unibo_motor_task;

// fd globale per scrittura su pwm
static int pwm_fd;

/* create topic metadata */
//ORB_DEFINE(motor_output, motor_output_s);

__EXPORT int unibo_motor_output_main(int argc, char *argv[]);

int unibo_motor_output_thread_main(int argc, char *argv[]);

static void usage(const char *reason)
{
	if (reason)
	{
		warnx("%s\n", reason);
	}
	warnx("usage: unibo_motor_output {start|stop|status|test}\n");
	exit(1);
}

int32_t map(int32_t in, int32_t in_low, int32_t in_high, int32_t out_low, int32_t out_high)
{
	float temp;
	temp = ((float)in-(float)in_low)*((float)out_high-(float)out_low)/((float)in_high-(float)in_low)+(float)out_low;
	return (int32_t)temp;
}

// inizializzazione servo
void unibo_motor_output_init()
{
	int ret = 0;

	pwm_fd = open("/dev/pwm_output", O_RDWR);
	if (pwm_fd < 0)
	{
		warnx("cannot open fd\n");
		exit(1);
	}

	// eventuale impostazione PWM_SERVO_SET_UPDATE_RATE, vedi pwm.c

	ret = ioctl(pwm_fd, PWM_SERVO_ARM, 0);
	if (ret != OK)
	{
		warnx("errore arm\n");
		exit(1);
	}
	/*int i;
	warnx("Motor Output: initializing pwm at 950us");
	for(i = MOTORS_START; i < MOTORS_NUMBER; i++)
	{
		ioctl(pwm_fd, PWM_SERVO_SET(i), 900);
	}*/
}

// deinizializzazione servo
void unibo_motor_output_deinit()
{
	int ret;
	ret = ioctl(pwm_fd, PWM_SERVO_DISARM, 0);
	if (ret != OK)
	{
		warnx("errore disarm\n");
		exit(1);
	}
}

// test dei pin di output
void unibo_motor_output_test()
{
	warnx("[unibo_motor_output] testing... you should see 20 sec of output \"blinking\"\n");

	//unibo_motor_output_init();

	sleep(10);
	int i, k;
	for(i = 0; i < 5; i++)
	{
		for(k = MOTORS_START; k < MOTORS_NUMBER; k++)
		{
			ioctl(pwm_fd, PWM_SERVO_SET(k), 950);
		}
		warnx("Prova 950");
		sleep(1);

		for(k = MOTORS_START; k < MOTORS_NUMBER; k++)
		{
			ioctl(pwm_fd, PWM_SERVO_SET(k), 1000);
		}
		//warnx("Prova 1100");
		sleep(1);

		for(k = MOTORS_START; k < MOTORS_NUMBER; k++)
		{
			ioctl(pwm_fd, PWM_SERVO_SET(k), 1100);
		}
		//warnx("Prova 1150");
		sleep(1);

		for(k = MOTORS_START; k < MOTORS_NUMBER; k++)
		{
			ioctl(pwm_fd, PWM_SERVO_SET(k), 1000);
		}
		//warnx("Prova 1000");
		sleep(1);

		for(k = MOTORS_START; k < MOTORS_NUMBER; k++)
		{
			ioctl(pwm_fd, PWM_SERVO_SET(k), 900);
		}
		//warnx("Prova 900");
		sleep(1);

		for(k = MOTORS_START; k < MOTORS_NUMBER; k++)
		{
			ioctl(pwm_fd, PWM_SERVO_SET(k), 700);
		}
		//warnx("Prova 700");
		sleep(1);
	}

	unibo_motor_output_deinit();

	warnx("[unibo_motor_output] test completed.\n");
}


// gestore demone
int unibo_motor_output_main(int argc, char *argv[])
{
	// controllo argomenti
	/* OLD
	if(argc != 2 && argc != 3)
	{
		usage("wrong arguments length");
	}

	if(argc == 2 && (strcmp(argv[1], "start") == 0 || strcmp(argv[1], "test") == 0))
	{
		usage("start and test commands require {fmu|io}");
	}

	if(argc == 3 && (strcmp(argv[2], "fmu") != 0 && strcmp(argv[2], "io") != 0))
	{
		usage("second argument must be 'fmu' or 'io'");
	}
	*/
	if(argc != 2)
	{
		usage("wrong arguments length");
	}

	if (strcmp(argv[1], "start") == 0)
	{
		if (unibomo_thread_running)
		{
			warnx("daemon already running\n");
			exit(0);
		}

		unibomo_thread_should_exit = false;

		unibomo_unibo_motor_task = task_spawn_cmd("unibo_motor_output",
					SCHED_DEFAULT,//SCHED_RR,
					SCHED_PRIORITY_MAX - 11, //SCHED_PRIORITY_DEFAULT,
					2048,
					unibo_motor_output_thread_main,
					(argv) ? (const char **)&argv[2] : (const char **)NULL);

		warnx("Thread started PID: %d",unibomo_unibo_motor_task);
		exit(0);
	}

	if (strcmp(argv[1], "stop") == 0)
	{
		unibomo_thread_should_exit = true;
		exit(0);
	}

	if (strcmp(argv[1], "status") == 0)
	{
		if (unibomo_thread_running)
		{
			warnx("\tunibo_motor_output is running\n");
		}
		else
		{
			warnx("\tunibo_motor_output not started\n");
		}
		exit(0);
	}

	if (strcmp(argv[1], "test") == 0)
	{
		unibo_motor_output_test();
		exit(0);
	}

	usage("unrecognized command");
	exit(1);
}

// thread principale con loop
int unibo_motor_output_thread_main(int argc, char *argv[])
{
	int count=0;
	bool flag_armed;
	bool updated;
	uint8_t esc_state;
	uint16_t pwm;
	struct pwm_output_values esc_actual_pwm;
	int ret;
	int16_t temp_pwm;

	warnx("[unibo_motor_output] starting\n");
	unibomo_thread_running = true;

	// subscribe a ORB
	int motor_output_fd = orb_subscribe(ORB_ID(motor_output));

	/* subscribe to safety switch topic */
	int safety_fd = orb_subscribe(ORB_ID(safety));
	struct safety_s safety;

	/* subscribe to unibo vehicle status topic */
	int unibo_status_fd = orb_subscribe(ORB_ID(unibo_vehicle_status));
	struct unibo_vehicle_status_s unibo_status;

	struct pollfd fds[] = { { .fd = motor_output_fd, .events = POLLIN } };

	unibo_motor_output_init();

	int i;
	//int motor_mapping; // mapping dei motori differente fra l'ItopRIS e il quadrotor UNIBO
	struct motor_output_s motor_output;

	// loop dell'applicazione
	while (!unibomo_thread_should_exit)
	{
		/*count++;      //USED TO READ ACTUAL PWM VALUES ON CHANNELS
		if (count >= 1){
			count = 0;
			ret = ioctl(pwm_fd, PWM_SERVO_GET(1), (unsigned long)&esc_actual_pwm.values[1]);
			warnx("Actual PWM of channel 1: %d", esc_actual_pwm.values[1]);
//			ret = ioctl(pwm_fd, PWM_SERVO_GET(5), (unsigned long)&esc_actual_pwm.values[5]);
//			warnx("Actual PWM of channel 5: %d", esc_actual_pwm.values[5]);
		}*/
		count++;


		orb_check(safety_fd, &updated);
		if (updated){
			orb_copy(ORB_ID(safety), safety_fd, &safety);
		}

		orb_check(unibo_status_fd, &updated);
		if (updated){
			orb_copy(ORB_ID(unibo_vehicle_status), unibo_status_fd, &unibo_status);
		}

		if (!safety.safety_off){   //inverted-->safety_off true means safety on
			flag_armed = false;
			if (esc_state!=1)    //different from disarmed
			{
				for(i = MOTORS_START; i < MOTORS_NUMBER; i++)
				{
					ioctl(pwm_fd, PWM_SERVO_SET(i), PWM_DISARMED);
				}
				esc_state = 1;  //DISARM
				//warnx("DISARM: %d", PWM_DISARMED);
			}
		} else {                //safety on
			if (esc_state<3){
				flag_armed = true;
				//esc_state = 2; //ARM
				//warnx("ARM: %d", PWM_ARMED);
				for(i = MOTORS_START; i < MOTORS_NUMBER; i++)
				{
					ioctl(pwm_fd, PWM_SERVO_SET(i), PWM_ARMED);
				}
			}
		}



		// controllo se ci sono nuovi dati
		int poll_ret = poll(fds, 1, 100);
		if(poll_ret > 0)
		{
			if(fds[0].revents & POLLIN)
			{

				if (count >= 200){
					count = 0;
					//warnx("MOTOR OUTPUT: Commanded RPM: %d %d %d %d", motor_output.outputs_rpm[0], motor_output.outputs_rpm[1], motor_output.outputs_rpm[2], motor_output.outputs_rpm[3]);
				}
				// lettura ORB
				//warnx("Nuovo valore pwm: %d %d %d %d %d %d %d %d", pwm_values.outputs[0], pwm_values.outputs[1], pwm_values.outputs[2], pwm_values.outputs[3],pwm_values.outputs[4], pwm_values.outputs[5], pwm_values.outputs[6], pwm_values.outputs[7]);
				orb_copy(ORB_ID(motor_output), motor_output_fd, &motor_output);

				// scrittura su pin output
				//safety.safety_off;  -->true if safety is off

				if (flag_armed){
					if (unibo_status.flight_mode == FLIGHTMODE_PREFLIGHT){
						esc_state = 3; //PREFLIGHT
						//warnx("PREFLIGHT");
						for(i = MOTORS_START; i < MOTORS_NUMBER; i++)
						{
							ioctl(pwm_fd, PWM_SERVO_SET(i), PWM_PREFLIGHT);
						}
					}else if (unibo_status.flight_mode == FLIGHTMODE_STOP){
						esc_state = 5; //STOP
						for(i = MOTORS_START; i < MOTORS_NUMBER; i++)
						{
							ioctl(pwm_fd, PWM_SERVO_SET(i), PWM_ARMED);
						}
						//warnx("STOP: %d", PWM_DISARMED);
					}else{
						esc_state = 4; //SPEED CONTROL ON
						//warnx("CONTROL");
						if (RPM_MODE){
							for(i = MOTORS_START; i < MOTORS_NUMBER; i++)
								{
									//pwm = map(motor_output.outputs_rpm[i], MIN_RPM, MAX_RPM, MIN_PWM, MAX_PWM);
//									if (count >= 195){
//										warnx("PWM: %d", pwm);
//									}
									temp_pwm = map(motor_output.outputs_rpm[i], MIN_RPM, MAX_RPM, MIN_PWM, MAX_PWM);
									temp_pwm = (temp_pwm < PWM_PREFLIGHT) ? PWM_PREFLIGHT :  temp_pwm;
									ioctl(pwm_fd, PWM_SERVO_SET(i), temp_pwm);  //TODO put "pwm" instead of map(...) for readibility
								}
						}else {
							for(i = MOTORS_START; i < MOTORS_NUMBER; i++)
								{
									ioctl(pwm_fd, PWM_SERVO_SET(i), motor_output.outputs_pwm[i]);
								}
						}
					}
				}
				count++;
				/*for(i = MOTORS_START; i < MOTORS_NUMBER; i++)       //OLD
				{
#ifdef ATECH
					motor_mapping = i;
#endif
#ifdef IRIS
					switch (i){
						case 0:
							motor_mapping = 2;
							break;
						case 1:
							motor_mapping = 0;
							break;
						case 2:
							motor_mapping = 3;
							break;
						case 3:
							motor_mapping = 1;
							break;
					}
#endif

					//ioctl(pwm_fd, PWM_SERVO_SET(i), 1100);
					ioctl(pwm_fd, PWM_SERVO_SET(motor_mapping), pwm_values.outputs[i]);
				}*/                   //END OLD
			}
		}
	}

    unibo_motor_output_deinit();

    warnx("[unibo_motor_output] exiting.\n");

    unibomo_thread_running = false;

	return 0;
}

