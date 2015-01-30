/****************************************************************************
 *
 *   Copyright (C) 2012-2014 PX4 Development Team. All rights reserved.
 *   Author: Marco Bauer <marco@wtns.de>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file esc32_reader.cpp
 *
 * Driver/configurator for the Arduino/Esc32Reader.
 *
 * @author Michele Furci <michele.furci@unibo.it>
 *
 */

#include <nuttx/config.h>
#include <nuttx/sched.h>

#include <unistd.h>

#include <drivers/device/i2c.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <fcntl.h>
#include <poll.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include <nuttx/arch.h>
#include <nuttx/i2c.h>

#include <board_config.h>

#include <drivers/device/device.h>
#include <drivers/drv_pwm_output.h>
#include <drivers/drv_hrt.h>
#include <drivers/drv_rc_input.h>

#include <systemlib/systemlib.h>
#include <systemlib/err.h>
#include <systemlib/mixer/mixer.h>
#include <drivers/drv_mixer.h>

#include <sys/mount.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <uORB/uORB.h>

#include <uORB/topics/actuator_controls.h>
#include <uORB/topics/actuator_outputs.h>
#include <uORB/topics/actuator_armed.h>
#include <uORB/topics/safety.h>

#include <uORB/topics/esc_status.h>       //USED
#include <uORB/topics/motor_output.h>
#include <uORB/topics/unibo_vehicle_status.h>

#include <nuttx/i2c.h>
#include <nuttx/mtd.h>
#include <nuttx/fs/nxffs.h>
#include <nuttx/fs/ioctl.h>

#include <systemlib/err.h>

#define I2C_BUS_SPEED					400000
#define UPDATE_RATE						200
#define MAX_MOTORS 						8
#define N_MOTORS 						4      //UNIBO
#define BLCTRL_BASE_ADDR 				0x29

#define ESC_UORB_PUBLISH_DELAY			10000   //UNIBO CHANGE put at 100Hz
#define DEVICE_ADDRESS 0x52  //UNIBO

#define SPEED_CONTROL_RPM	0          //Invert if we control with rpm //TODO do it better with #ifdef
#define SPEED_CONTROL_PWM	1


struct MotorData_t {
	unsigned int Version;                        // the version of the BL (0 = old)
	unsigned int SetPoint;                       // written by attitude controller
	unsigned int SetPointLowerBits;      		// for higher Resolution of new BLs
	float SetPoint_PX4; 			     		// Values from PX4
	unsigned int State;                          // 7 bit for I2C error counter, highest bit indicates if motor is present
	unsigned int ReadMode;                       // select data to read
	unsigned short RawPwmValue;					// length of PWM pulse
	// the following bytes must be exactly in that order!
	unsigned int Current;                        // in 0.1 A steps, read back from BL
	unsigned int MaxPWM;                         // read back from BL is less than 255 if BL is in current limit
	unsigned int Temperature;            		// old BL-Ctrl will return a 255 here, the new version the temp. in
	unsigned int RoundCount;
};

class ESC32_READER : public device::I2C
{
public:

	ESC32_READER(int bus, const char *_device_path);
	~ESC32_READER();

	virtual int	init();

private:
	static const unsigned _max_actuators = MAX_MOTORS;
	static const bool	showDebug = false;

	//int 		_update_rate;
	//int 		_current_update_rate;
	int		_task;                   //TODO cleanup and reorganization (too many function call)
	int		_t_actuators;
	int		_t_actuator_armed;
	int		_arduino_counter;
	esc_status_s 		_esc;
	unsigned int		_motor;
	int    _px4mode;
	int    _frametype;
	char				_device[20];					///< device

	orb_advert_t	_t_outputs;
	orb_advert_t	_t_esc_status;

	unsigned int	_num_outputs;
	bool		_primary_pwm_device;
	bool     _motortest;
	bool 		_overrideSecurityChecks;

	volatile bool	_task_should_exit;
	bool		_armed;

	unsigned long	debugCounter;

	MixerGroup	*_mixers;

	actuator_controls_s _controls;

	MotorData_t Motor[MAX_MOTORS];

	static void	task_main_trampoline(int argc, char *argv[]);
	void		task_main();


	struct GPIOConfig {
		uint32_t	input;
		uint32_t	output;
		uint32_t	alt;
	};

	static const GPIOConfig	_gpio_tab[];
	static const unsigned	_ngpio;

	int			read_arduino(unsigned int add);    //UNIBO
	int			send_pwm(uint16_t pwm_values[4], uint8_t esc_state, unsigned int add);    //UNIBO
};



namespace
{

ESC32_READER	*g_esc32_reader;

} // namespace

ESC32_READER::ESC32_READER(int bus, const char *_device_path) :
	I2C("esc32_reader", "/dev/esc32_reader", bus, DEVICE_ADDRESS, I2C_BUS_SPEED),
	//_update_rate(400),
	_task(-1),
	_t_actuators(-1),
	_t_actuator_armed(-1),
	_arduino_counter(0),
	_motor(-1),
	_t_outputs(0),
	_t_esc_status(0),
	_num_outputs(0),
	_primary_pwm_device(false),
	_motortest(false),
	_overrideSecurityChecks(true),   //unibo-->true
	_task_should_exit(false),
	_armed(false),
	_mixers(nullptr)
{
	strncpy(_device, _device_path, sizeof(_device));
	/* enforce null termination */
	_device[sizeof(_device) - 1] = '\0';

	_debug_enabled = true;
}

ESC32_READER::~ESC32_READER()
{
	if (_task != -1) {
		/* tell the task we want it to go away */
		_task_should_exit = true;

		unsigned i = 10;

		do {
			/* wait 50ms - it should wake every 100ms or so worst-case */
			usleep(50000);

			/* if we have given up, kill it */
			if (--i == 0) {
				task_delete(_task);
				break;
			}

		} while (_task != -1);
	}

	/* clean up the alternate device node */
	if (_primary_pwm_device)
		unregister_driver(_device);

	g_esc32_reader = nullptr;
}

int
ESC32_READER::init()
{
	int ret;
	ASSERT(_task == -1);

	ret = I2C::init();

	if (ret != OK) {
		warnx("I2C init failed");
		return ret;
	}

	usleep(500000);

	if (sizeof(_device) > 0) {
		ret = register_driver(_device, &fops, 0666, (void *)this);

		if (ret == OK) {
			log("creating alternate output device");
			_primary_pwm_device = true;
		}

	}

	/* start the IO interface task */
	_task = task_spawn_cmd("esc32_reader",
			       SCHED_DEFAULT,
			       SCHED_PRIORITY_MAX - 20,
			       2048,
			       (main_t)&ESC32_READER::task_main_trampoline,
			       nullptr);


	if (_task < 0) {
		debug("task start failed: %d", errno);
		return -errno;
	}

	return OK;
}

void
ESC32_READER::task_main_trampoline(int argc, char *argv[])
{
	g_esc32_reader->task_main();
}



void
ESC32_READER::task_main()
{
	bool updated;
	bool flag_armed = false;
	int temp_counter = 0;
	uint8_t esc_state;  //to be sent to esc 0-->invalid, 1-->disarm, 2-->arm, 3-->preflight, 4-->control, 5-->stop
	int8_t esc_state_byte; //packed byte 00xxxxyy xxxx-->esc_state, yy-->velocity mode
	uint8_t velocity_mode;

	/* advertise the blctrl status */
	esc_status_s esc;
	memset(&esc, 0, sizeof(esc));
	_t_esc_status = orb_advertise(ORB_ID(esc_status), &esc);

	/* subscribe to safety switch topic */
	int safety_fd = orb_subscribe(ORB_ID(safety));
	struct safety_s safety;

	/* subscribe to unibo vehicle status topic */
	int unibo_status_fd = orb_subscribe(ORB_ID(unibo_vehicle_status));
	struct unibo_vehicle_status_s unibo_status;

	/* subscribe to motor output topic */
	int motor_output_fd = orb_subscribe(ORB_ID(motor_output));
	struct motor_output_s pwm_values;

	//struct pollfd fds[] = { { .fd = motor_output_fd, .events = POLLIN } };
	pollfd fds[1];
	fds[0].fd = motor_output_fd;
	fds[0].events = POLLIN;

	warnx("I2C reader starting");
	uint16_t pwm_motors[N_MOTORS];

	/* loop until killed */
	while (!_task_should_exit) {

		int ret = ::poll(&fds[0], 1, 100);         //should be at 200Hz
		if(ret > 0){
			if(fds[0].revents & POLLIN){
				orb_check(motor_output_fd, &updated);
				if (updated){
					orb_copy(ORB_ID(motor_output), motor_output_fd, &pwm_values);
				}


				/* copy safety switch data into local buffer */
				/*
				orb_check(safety_fd, &updated);
				if (updated){
					orb_copy(ORB_ID(safety), safety_fd, &safety);
					//safety.safety_off;  -->true if safety is off
				}
				orb_check(unibo_status_fd, &updated);
				if (updated){
					orb_copy(ORB_ID(unibo_vehicle_status), unibo_status_fd, &unibo_status);
				}

				if (!safety.safety_off){
					flag_armed = false;
					esc_state = 1;  //DISARM
				} else{
					if (!flag_armed){
						flag_armed = true;
						esc_state = 2; //ARM
					} else{
						if (unibo_status.flight_mode == FLIGHTMODE_PREFLIGHT){
							esc_state = 3; //PREFLIGHT
						}else if (unibo_status.flight_mode == FLIGHTMODE_STOP){
							esc_state = 5; //STOP
						}
						else{
							esc_state = 4; //SPEED CONTROL ON
						}
					}
				}*/


				/*esc_state_byte = 0;
				esc_state_byte = esc_state_byte | (esc_state << 2);
				//warnx("esc_status2: %d", esc_state_byte);
				if (SPEED_CONTROL_PWM){
					velocity_mode = 1;
					esc_state_byte = esc_state_byte | velocity_mode;
					//warnx("esc_status3: %d", esc_state_byte);
				}else{
					velocity_mode = 2;
					esc_state_byte = esc_state_byte | velocity_mode;
					//warnx("esc_status3: %d", esc_state_byte);
				}*/

				//warnx("esc_status: %d", esc_state_byte);
				read_arduino(DEVICE_ADDRESS);
				if (_arduino_counter>=200){
					_arduino_counter = 0;
					warnx("Speeds: %d - %d - %d - %d", _esc.esc[0].esc_rpm, _esc.esc[1].esc_rpm, _esc.esc[2].esc_rpm, _esc.esc[3].esc_rpm);
				}

				/*temp_counter++;        //TODO remove to have full 200Hz
				if (temp_counter >=200){
					temp_counter = 0;
					for (int i =0; i<N_MOTORS;i++){
						pwm_motors[i] = pwm_values.outputs[i];
					}
					if (OK == send_pwm(pwm_motors, esc_state_byte, DEVICE_ADDRESS)){

					}
				}*/

				esc = _esc;
				orb_publish(ORB_ID(esc_status), _t_esc_status, &esc);
			}
		}

		/*if (hrt_absolute_time() - esc.timestamp > ESC_UORB_PUBLISH_DELAY) {
					esc.timestamp = hrt_absolute_time();
					read_arduino(DEVICE_ADDRESS);   //UNIBO
		}
		usleep(ESC_UORB_PUBLISH_DELAY/2);*/

		/*if (hrt_absolute_time() - esc.timestamp > ESC_UORB_PUBLISH_DELAY) {
			esc.counter++;
			esc.timestamp = hrt_absolute_time();


		}*/

	}

	::close(_t_esc_status);
	::close(_t_actuators);
	::close(_t_actuator_armed);


	/* make sure servos are off */
	up_pwm_servo_deinit();

	log("stopping");

	/* note - someone else is responsible for restoring the GPIO config */

	/* tell the dtor that we are exiting */
	_task = -1;
	_exit(0);
}


int
ESC32_READER::read_arduino(unsigned int add)         //UNIBO
{
	uint8_t message[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	set_address(add);
	if (OK == transfer(nullptr, 0, &message[0], 8)) {
		uint16_t* speeds = (uint16_t*)message;
		_esc.counter++;
		_esc.esc[0].esc_rpm = speeds[0];
		_esc.esc[1].esc_rpm = speeds[1];
		_esc.esc[2].esc_rpm = speeds[2];
		_esc.esc[3].esc_rpm = speeds[3];
		//TODO add current, voltage, temperature,...
		//TODO merge with single function to read/write
		_arduino_counter++;
		return OK;
	}
}

int
ESC32_READER::send_pwm(uint16_t pwm_values[4], uint8_t esc_state, unsigned int add)         //UNIBO
{
	uint8_t message[9];
	message[0] = esc_state;
	for (int i = 1; i<4;i++){ //filling 1...8
		message[i*2-1] = pwm_values [i] & 0xff;
		message[i*2] = pwm_values [i] >> 8;
	}
	set_address(add);
	if (OK == transfer(&message[0], 9, nullptr, 0)) {
		return OK;
	}
}

namespace
{


int
esc32_reader_start(const char *device_path)
{
	int ret;

	// try i2c0 first
	/*
	g_esc32_reader = new ESC32_READER(0, device_path);   //UNIBO bus=3-->bus=0

	if (!g_esc32_reader)
		return -ENOMEM;

	warnx("Testing i2c0...");
	if (OK == g_esc32_reader->init(motors)) {
		warnx("[esc32_reader] scanning i2c0...\n");
		return OK;
	}

	delete g_esc32_reader;
	g_esc32_reader = nullptr;*/

	// fallback to bus 1        seems to work UNIBO
	g_esc32_reader = new ESC32_READER(1, device_path);

	if (!g_esc32_reader)
		return -ENOMEM;

	warnx("Testing i2c1...");
	if (OK == g_esc32_reader->init()) {
		warnx("[esc32_reader] scanning i2c1...\n");
		return OK;
	}

	delete g_esc32_reader;
	g_esc32_reader = nullptr;

	return -ENXIO;
}


} // namespace

extern "C" __EXPORT int esc32_reader_main(int argc, char *argv[]);

int
esc32_reader_main(int argc, char *argv[])
{
	const char *devicepath = "";

	/*
	 * optional parameters
	 */
	/*    REMOVED
	for (int i = 1; i < argc; i++) {


		if (strcmp(argv[i], "-mkmode") == 0 || strcmp(argv[i], "--mkmode") == 0) {
			if (argc > i + 1) {
				if (strcmp(argv[i + 1], "+") == 0 || strcmp(argv[i + 1], "x") == 0 || strcmp(argv[i + 1], "X") == 0) {
					px4mode = MAPPING_MK;
					newMode = true;

					if (strcmp(argv[i + 1], "+") == 0) {
						frametype = FRAME_PLUS;

					} else {
						frametype = FRAME_X;
					}

				} else {
					errx(1, "only + or x for frametype supported !");
				}

			} else {
				errx(1, "missing argument for mkmode (-mkmode)");
				return 1;
			}
		}


		if (strcmp(argv[i], "-t") == 0) {
			motortest = true;
			newMode = true;
		}


		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			showHelp = true;
		}


		if (strcmp(argv[i], "--override-security-checks") == 0) {
			overrideSecurityChecks = true;
			newMode = true;
		}


		if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--device") == 0) {
			if (argc > i + 1) {
				devicepath = argv[i + 1];
				newMode = true;

			} else {
				errx(1, "missing the devicename (-d)");
				return 1;
			}
		}

	} */     //END REMOVED

	/* REMOVED
	if (showHelp) {
		fprintf(stderr, "esc32_reader: help:\n");
		fprintf(stderr, "  [-mkmode {+/x}] [-b i2c_bus_number] [-d devicename] [--override-security-checks] [-h / --help]\n\n");
		fprintf(stderr, "\t -mkmode {+/x} \t\t Type of frame, if Mikrokopter motor order is used.\n");
		fprintf(stderr, "\t -d {devicepath & name}\t\t Create alternate pwm device.\n");
		fprintf(stderr, "\t --override-security-checks \t\t Disable all security checks (arming and number of ESCs). Used to test single Motors etc. (DANGER !!!)\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "Motortest:\n");
		fprintf(stderr, "First you have to start esc32_reader, the you can enter Motortest Mode with:\n");
		fprintf(stderr, "esc32_reader -t\n");
		fprintf(stderr, "This will spin up once every motor in order of motoraddress. (DANGER !!!)\n");
		exit(1);
	}
	*/  //END REMOVED


	//ADDED
	if (esc32_reader_start(devicepath) != OK) {
		errx(1, "failed to start the ESC32_READER-BLCtrl driver");
	}
}
