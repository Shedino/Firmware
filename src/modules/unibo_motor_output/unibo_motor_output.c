/*
 *
 * Filename: set_motor_output.c
 * Authors: Luca De Luigi, Paolo Di Febbo
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

//#include <uORB/uORB.h>
#include <uORB/topics/motor_output.h>

#include <nuttx/i2c.h>
#include <nuttx/mtd.h>
#include <nuttx/fs/nxffs.h>
#include <nuttx/fs/ioctl.h>

#include <drivers/drv_pwm_output.h>

// numero di motori effettivamente collegati
#define MOTORS_NUMBER 8

// globali per thread
static bool thread_should_exit = false;
static bool thread_running = false;
static int daemon_task;

// fd globale per scrittura su pwm
int pwm_fd;

/* create topic metadata */
//ORB_DEFINE(motor_output, motor_output_s);

__EXPORT int unibo_motor_output_main(int argc, char *argv[]);

int unibo_motor_output_thread_main(int argc, char *argv[]);

static void usage(const char *reason)
{
	if (reason)
	{
		fprintf(stderr, "%s\n", reason);
	}
	fprintf(stderr, "usage: unibo_motor_output {start|stop|status|test}\n");
	exit(1);
}

// inizializzazione servo
void unibo_motor_output_init()
{
	int ret = 0;

	pwm_fd = open("/dev/pwm_output", 0);
	if (pwm_fd < 0)
	{
		printf("cannot open fd\n");
		exit(1);
	}

	// eventuale impostazione PWM_SERVO_SET_UPDATE_RATE, vedi pwm.c

	ret = ioctl(pwm_fd, PWM_SERVO_ARM, 0);
	if (ret != OK)
	{
		printf("errore arm\n");
		exit(1);
	}
}

// deinizializzazione servo
void unibo_motor_output_deinit()
{
	int ret;
	ret = ioctl(pwm_fd, PWM_SERVO_DISARM, 0);
	if (ret != OK)
	{
		printf("errore disarm\n");
		exit(1);
	}
}

// test dei pin di output
void unibo_motor_output_test()
{
	printf("[unibo_motor_output] testing... you should see 6 sec of output \"blinking\"\n");

	unibo_motor_output_init();

	int i, k;
	for(i = 0; i < 3; i++)
	{
		for(k = 0; k < MOTORS_NUMBER; k++)
		{
			ioctl(pwm_fd, PWM_SERVO_SET(k), 0);
		}
		sleep(1);

		for(k = 0; k < MOTORS_NUMBER; k++)
		{
			ioctl(pwm_fd, PWM_SERVO_SET(k), 1200);
		}
		sleep(1);
	}

	unibo_motor_output_deinit();

	printf("[unibo_motor_output] test completed.\n");
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
		if (thread_running)
		{
			printf("daemon already running\n");
			exit(0);
		}

		thread_should_exit = false;

		daemon_task = task_spawn("unibo_motor_output",
					 SCHED_RR,
					 SCHED_PRIORITY_DEFAULT,
					 4096,
					 unibo_motor_output_thread_main,
					 (argv) ? (const char **)&argv[2] : (const char **)NULL);

		exit(0);
	}

	if (strcmp(argv[1], "stop") == 0)
	{
		thread_should_exit = true;
		exit(0);
	}

	if (strcmp(argv[1], "status") == 0)
	{
		if (thread_running)
		{
			printf("\tunibo_motor_output is running\n");
		}
		else
		{
			printf("\tunibo_motor_output not started\n");
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
	printf("[unibo_motor_output] starting\n");
    thread_running = true;

	// subscribe a ORB
	int motor_output_fd = orb_subscribe(ORB_ID(motor_output));
	// orb_set_interval(motor_output_fd, 1000);

	struct pollfd fds[] = { { .fd = motor_output_fd, .events = POLLIN } };

	unibo_motor_output_init();

	int i;
	struct motor_output_s pwm_values;

	// loop dell'applicazione
	while (!thread_should_exit)
	{
		// controllo se ci sono nuovi dati
		int poll_ret = poll(fds, 1, 1000);
		if(poll_ret > 0)
		{
			if(fds[0].revents & POLLIN)
			{
				// lettura ORB
				orb_copy(ORB_ID(motor_output), motor_output_fd, &pwm_values);

				// scrittura su pin output
				for(i = 0; i < MOTORS_NUMBER; i++)
				{
					ioctl(pwm_fd, PWM_SERVO_SET(i), pwm_values.outputs[i]);
				}
			}
		}
	}

    unibo_motor_output_deinit();

	printf("[unibo_motor_output] exiting.\n");

	thread_running = false;

	return 0;
}

