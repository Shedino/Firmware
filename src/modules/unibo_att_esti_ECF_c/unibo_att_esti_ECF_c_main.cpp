/****************************************************************************
 *
 *   Copyright (C) 2013 PX4 Development Team. All rights reserved.
 *   Author: Mohammad R. M. Hayajneh <hayajneh09@gmail.com>
 *           						<mohammad.hayajneh3@unibo.it>
 *   Reference: Hyon Lim <limhyon@gmail.com>
 *           	Anton Babushkin <anton.babushkin@me.com>
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
 
/* @file unibo_att_esti_ECF_c_main.cpp
 * By Mohammad R. M. Hayajneh <hayajneh09@gmail.com>
// *           					   <mohammad.hayajneh3@unibo.it>
 * University of Bologna_ CASY Lab
 *--------------------------------------------------------------------------
 * This work provides an implementation of nonlinear filter on Autopilot board to show its
 * performance for attainment the best attitude estimation
 * The filter is well known as explicit complementary filter (ECF) has been introduced in [1] and [2].
 * The filter was designed explicitly in terms of direct and raw measurements from low-cost inertial
 * measurement unit (IMU).
 * Result is provided in quaternion
 *
 * Rrferences:
 * [1] T. Hamel and R. Mahony. Attitude estimation on SO(3) based on direct inertial measurements. In IEEE Conf.
 *  on Robotics and Automation, pages 2170–2175, 2006.
 * [2] R. Mahony, T. Hamel, and J.-M. Pflimlin. Nonlinear complementary filters on the special orthogonal group.
 * IEEE Trans. on Automatic Control, 53(5):1203–1218, 2008.
 * [3] Minh-Duc Hua, G. Ducard, T. Hamel, R. Mahony, and K. Rudin “ Implementation of a Nonlinear Attitude Estimator
 * for Aerial Robotic Vehicles”, IEEE TRANSACTIONS ON CONTROL SYSTEMS TECHNOLOGY, 2014.
 *
 */

#include <errno.h>			// Last error number (macro )
#include <fcntl.h>			// file control options (Unix)
#include <float.h>			// floating types for the specific system and compiler
//#include <iomanip> 		// for setprecision(n),n:number of digits
#include <limits.h>			// Sizes of integral types
#include <math.h>			// compute common mathematical operations
#include <poll.h>			// definitions for the poll() function
#include <nuttx/config.h>	// configuration file will be used at build time
#include <nuttx/sched.h>
#include <unistd.h>			// provides access to the POSIX OS (Unix)
#include <stdbool.h>		// Boolean type
#include <stdio.h>			// perform Input/Output operations
#include <stdlib.h>			// Standard General Utilities Library
#include <string.h>			// manipulate C strings and arrays
#include <sys/prctl.h>
#include <termios.h>

#include <drivers/drv_hrt.h>					// open Declaration
#include <uORB/topics/debug_key_value.h>		// open Declaration
#include <uORB/topics/parameter_update.h>		// open Declaration
#include <uORB/topics/sensor_combined.h>		// open Declaration
#include <uORB/topics/vehicle_attitude.h>		// open Declaration
#include <uORB/topics/vehicle_control_mode.h>	// open Declaration
#include <uORB/uORB.h>							// open Declaration

#include <systemlib/systemlib.h>
#include <systemlib/perf_counter.h>
#include <systemlib/err.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "unibo_att_esti_ECF_c_params.h"
#ifdef __cplusplus
}
#endif

extern "C" __EXPORT int unibo_att_esti_ECF_c_main(int argc, char *argv[]);

static bool thread_should_exit = false;		/**< Deamon exit flag */
static bool thread_running = false;		/**< Deamon status flag */
static int unibo_att_esti_ECF_c_task;				/**< Handle of deamon task / thread */


// use floating point numbers
static float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;		//quaternion of inertial reference frame to body frame
static float dq0 = 0.0f, dq1 = 0.0f, dq2 = 0.0f, dq3 = 0.0f;	//quaternion of inertial reference frame to body frame
static float gyro_bias[3] = {0.0f, 0.0f, 0.0f}; 				//gyro bias

// variables to simplify the calculations
static float q0q0, q0q1, q0q2, q0q3;
static float q1q1, q1q2, q1q3;
static float q2q2, q2q3;
static float q3q3;

static bool bFilterInit = false;

 //Mainloop of unibo_att_esti_ECF_c.
int unibo_att_esti_ECF_c_thread_main(int argc, char *argv[]);

/**
 * Print the correct usage.
 */
static void usage(const char *reason);

// Internal Functions
void standardECFinit(float ax, float ay, float az, float mx, float my, float mz);
void standardECFnew(float gx, float gy, float gz, float bx, float by, float bz, float ax, float ay, float az, float mx, float my, float mz,float twoK1, float twoK2, float twoK3, float twoK4, float twoKb, float delta, float dt);

static void
usage(const char *reason)
{
	if (reason)
		fprintf(stderr, "%s\n", reason);

	fprintf(stderr, "usage: unibo_att_esti_ECF_c {start|stop|status}\n");
	exit(1);
}

/**
 * The unibo_att_esti_ECF_c app only briefly exists to start
 * the background job. The stack size assigned in the
 * Makefile does only apply to this management task.
 *
 * The actual stack size should be set in the call
 * to task_create().
 */
int unibo_att_esti_ECF_c_main(int argc, char *argv[])
{
	if (argc < 1)
		usage("missing command");

	if (!strcmp(argv[1], "start")) {

		if (thread_running) {
			warnx("already running\n");
			/* this is not an error */
			exit(0);
		}

		thread_should_exit = false;
		unibo_att_esti_ECF_c_task = task_spawn_cmd("unibo_att_esti_ECF_c",
					      SCHED_DEFAULT,
					      SCHED_PRIORITY_MAX - 5,
					      2048,
					      unibo_att_esti_ECF_c_thread_main,
					      (argv) ? (const char **)&argv[2] : (const char **)NULL);
		exit(0);
	}

	if (!strcmp(argv[1], "stop")) {
		thread_should_exit = true;

		while (thread_running){
			usleep(200000);
		}
		
		warnx("stopped");
		exit(0);
	}

	if (!strcmp(argv[1], "status")) {
		if (thread_running) {
			warnx("running");
			exit(0);

		} else {
			warnx("not started");
			exit(1);
		}

		exit(0);
	}

	usage("unrecognized command");
	exit(1);
}

/*
 * initializing the filter
 * computing Roll(fi) and Pitch (theta) usign the Accelerometer readings
 * computing Yaw (psi) using the Magnetometer readings then to find the corresponding
 * initial quaternion
 */
void standardECFinit(float ax, float ay, float az, float mx, float my, float mz)
{
    float initialRoll, cosRoll, sinRoll;
    float initialPitch, cosPitch, sinPitch;
    float initialYaw, cosYaw, sinYaw;
    float magX, magY;

    // find initial values of Roll (Phi) and Pitch(theta) from accelerometer

    initialRoll = atan2(ay, az);			// Initial Roll

    // find cosine and sine for Roll and use to find Pitch and Yaw
    cosRoll = cosf(initialRoll);
    sinRoll = sinf(initialRoll);

    initialPitch = atan2f(-ax * cosRoll , az);	// Initial pitch

    // find cosine and sine for Pitch and use to find Yaw
    cosPitch = cosf(initialPitch);
    sinPitch = sinf(initialPitch);

    // find initial value of Yaw (psi) from magnetometer measurment
    magX = mx * cosPitch + my * sinRoll * sinPitch + mz * cosRoll * sinPitch;
    magY = my * cosRoll - mz * sinRoll;

    initialYaw = atan2f(-magY, magX);		// Initial Yaw

    // find initial quaternion
    cosRoll = cosf(initialRoll * 0.5f);
    sinRoll = sinf(initialRoll * 0.5f);

    cosPitch = cosf(initialPitch * 0.5f);
    sinPitch = sinf(initialPitch * 0.5f);

    cosYaw = cosf(initialYaw * 0.5f);
    sinYaw= sinf(initialYaw * 0.5f);

    q0 = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;
    q1 = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
    q2 = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
    q3 = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;

    // simplify calculations
    q0q0 = q0 * q0;
    q0q1 = q0 * q1;
    q0q2 = q0 * q2;
    q0q3 = q0 * q3;
    q1q1 = q1 * q1;
    q1q2 = q1 * q2;
    q1q3 = q1 * q3;
    q2q2 = q2 * q2;
    q2q3 = q2 * q3;
    q3q3 = q3 * q3;
	warnx("Initial euler angles in degrees:");
	warnx("%.3f %.3f %.3f",  	initialRoll  * 57.2727f,
								initialPitch * 57.2727f,
								initialYaw   * 57.2727f);
}
// initialization end


void standardECFnew(float gx, float gy, float gz, float bx, float by, float bz, float ax, float ay, float az, float mx, float my, float mz, float twoK1, float twoK2, float twoK3, float twoK4, float twoKb , float delta, float dt)
{
	float VectorNorm, asquare;
	float axe = 0.0f, aye = 0.0f, aze = 0.0f;	// estimatied Accelerometer vector

	float vBx , vBy, vBz;	// decoupled Magnetometer vector

	float Verrx = 0.0f, Verry = 0.0f, Verrz = 0.0f; // Magnetometer vector error
	float Uerrx = 0.0f, Uerry = 0.0f, Uerrz = 0.0f; // Acclerometer vector error

	// Reference direction of Earth magnetic field (normalized)
		//float mIx=0.1833f, mIy=0.0332f, mIz=0.5340f;	//for Bologna in Gause
	  float mIx, mIy, mIz;

	// Make filter converge to initial solution faster
	if(bFilterInit == false) {
		standardECFinit(ax,ay,az,mx,my,mz);
		bFilterInit = true;
	}

    	// use normalaized accelrometer vector for decoupling
		ax /= 9.82f;
		ay /= 9.82f;
		az /= 9.82f;

	// use Magnetometer readings if available .
	if(!((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f))) {

		float mxe, mye, mze;

    	VectorNorm = sqrtf(mx * mx + my * my + mz * mz);
    	mx /= VectorNorm;
    	my /= VectorNorm;
    	mIx = 2.0f * (mx * (0.5f - q2q2 - q3q3) + my * (q1q2 - q0q3) + mz * (q1q3 + q0q2));
    	mIy = 2.0f * (mx * (q1q2 + q0q3) + my * (0.5f - q1q1 - q3q3) + mz * (q2q3 - q0q1));
		//hz = 2.0f * mx * (q1q3 - q0q2) + 2.0f * my * (q2q3 + q0q1) + 2.0f * mz * (0.5f - q1q1 - q2q2);
    	//bx = sqrt(hx * hx + hy * hy);
    	//bz = hz;
    	//warnx("%.3f %.3f",  	mIx, mIy);
	
		asquare = (ax * ax + ay * ay+ az * az );
		// Normalise magnetic feild in inertial frame and decouple
		VectorNorm = sqrtf(mIx * mIx + mIy * mIy );
		mIx /= VectorNorm;
    	mIy /= VectorNorm;
    	mIz = 0.0f;

    	// Normalise Magnetometer vector in body frame and decouple
    	vBx = mx*(asquare  - ax*ax) - my*ax*ay - mz*ax*az;
    	vBy = my*(asquare  - ay*ay) - mx*ax*ay - mz*ay*az;
    	vBz = mz*(asquare  - az*az) - mx*ax*az - my*ay*az;
    	vBx /=VectorNorm;
    	vBy /=VectorNorm;
    	vBz /=VectorNorm;
    	// Estimated direction of magnetic vector in body frame represented in inertial frame
    	// m=inv(q)(X)mg(X)q : inv:= inverse, (X):= quatrnion multiplication
    	// mg is the local earth magnetic feild
    	mxe = mIx*q0q0 + 2.0f*mIy*q0q3 + mIx*q1q1 + 2.0f*mIy*q1q2 - mIx*q2q2 - mIx*q3q3;
    	mye = mIy*q0q0 - 2.0f*mIx*q0q3 - mIy*q1q1 + 2.0f*mIx*q1q2 + mIy*q2q2 - mIy*q3q3;
    	mze = 2.0f*mIx*q0q2 - 2.0f*mIy*q0q1  + 2.0f*mIx*q1q3 + 2.0f*mIy*q2q3;

    	//mxe= mIx*q0q0 - 2.0f*mIz*q0q2 + 2.0f*mIy*q0q3 + mIx*q1q1 + 2.0f*mIy*q1q2 + 2.0f*mIz*q1q3 - mIx*q2q2 - mIx*q3q3;
    	//mye= mIy*q0q0 + 2.0f*mIz*q0q1 - 2.0f*mIx*q0q3 - mIy*q1q1 + 2.0f*mIx*q1q2 + mIy*q2q2 + 2.0f*mIz*q2q3 - mIy*q3q3;
    	//mze= mIz*q0q0 - 2.0f*mIy*q0q1 + 2.0f*mIx*q0q2 - mIz*q1q1 + 2.0f*mIx*q1q3 - mIz*q2q2 + 2.0f*mIy*q2q3 + mIz*q3q3;
    
    	// cross product between measured vector and estimated vector
    	// to caculate the error in magnetometer measurments
    	Verrx += (vBy * mze - vBz * mye);
    	Verry += (vBz * mxe - vBx * mze);
    	Verrz += (vBx * mye - vBy * mxe);
	}

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {


		// Estimated direction of gravity vector represented in body frame
    	// ae=inv(q)(X)e3q(X)q : inv:= inverse, (X):= quatrnion multiplication
		// e3q=[0 0 0 1]'

		axe += 2.0f*(q1q3 - q0q2);
		aye += 2.0f*(q0q1 + q2q3);
		aze += q0q0 - q1q1 - q2q2+ q3q3;
	
		// cross product between measured vector and estimated vector
		// to caculate the error in Accelerometer measurments

		Uerrx += (ay * aze - az * aye);
		Uerry += (az * axe - ax * aze);
		Uerrz += (ax * aye - ay * axe);

	}

	// Apply feedback only when valid data has been gathered from the accelerometer

	if(Uerrx != 0.0f && Uerry != 0.0f && Uerrz != 0.0f) {
		// Compute and apply integral feedback if enabled


		if(twoK3 > 0.0f && twoK4 > 0.0f) {

			// bound bias in roll

			if ((delta/abs(bx))< 1.0f){

				gyro_bias[0] += (twoKb*bx -(twoKb * bx* delta / abs(bx)) + twoK3 * Uerrx + twoK4*Verrx) * dt;

			}
			else {
				gyro_bias[0] += (twoK3 * Uerrx + twoK4*Verrx) * dt;
			}
			// bound bias in pitch
			if (by > (delta/by)){
				gyro_bias[1] += (twoKb*by -(twoKb * by* delta / abs(by)) + twoK3 * Uerry + twoK4*Verry) * dt;
			}
			else{
				gyro_bias[1] += (twoK3 * Uerry + twoK4*Verry) * dt;
			}
			// bound bias in Yaw
			if (bz > (delta/bz)){
				gyro_bias[2] += (twoKb*bz -(twoKb * bz* delta / abs(bz))+ twoK3 * Uerrz + twoK4*Verrz) * dt;
			}
			else {
				gyro_bias[2] += (twoK3 * Uerrz + twoK4*Verrz) * dt;
			}

			// apply integral feedback
			gx += gyro_bias[0];
			gy += gyro_bias[1];
			gz += gyro_bias[2];
		}
		else {
			gyro_bias[0] = 0.0f;	// prevent integral windup
			gyro_bias[1] = 0.0f;
			gyro_bias[2] = 0.0f;
		}
		// use bias values for next iteration
		bx = gyro_bias[0];
		by = gyro_bias[1];
		bz = gyro_bias[2];

		// use the proportional gains (k1 and k2) for sensors in the correction term
		gx += twoK1 * Uerrx + twoK2 * axe *(Verrx * axe + Verry * aye + Verrz * aze);
		gy += twoK1 * Uerry + twoK2 * aye *(Verrx * axe + Verry * aye + Verrz * aze);
		gz += twoK1 * Uerrz + twoK2 * aze *(Verrx * axe + Verry * aye + Verrz * aze);

	}
	
	//! Integrate rate of change of quaternion
#if 0
	gx *= (0.5f * dt);		// pre-multiply common factors
	gy *= (0.5f * dt);
	gz *= (0.5f * dt);
#endif 

	// Time derivative of quaternion. q_dot = 0.5*q\otimes omega.
	//! q_k = q_{k-1} + dt*\dot{q}
	//! \dot{q} = 0.5*q \otimes P(\omega)
	dq0 = 0.5f*(-q1 * gx - q2 * gy - q3 * gz);
	dq1 = 0.5f*(q0 * gx + q2 * gz - q3 * gy);
	dq2 = 0.5f*(q0 * gy - q1 * gz + q3 * gx);
	dq3 = 0.5f*(q0 * gz + q1 * gy - q2 * gx); 

	q0 += dt*dq0;
	q1 += dt*dq1;
	q2 += dt*dq2;
	q3 += dt*dq3;
	
	// Normalise quaternion
	VectorNorm = sqrtf(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 /= VectorNorm;
	q1 /= VectorNorm;
	q2 /= VectorNorm;
	q3 /= VectorNorm;

	// simplify calculations
    q0q0 = q0 * q0;
    q0q1 = q0 * q1;
    q0q2 = q0 * q2;
    q0q3 = q0 * q3;
    q1q1 = q1 * q1;
    q1q2 = q1 * q2;
   	q1q3 = q1 * q3;
    q2q2 = q2 * q2;
    q2q3 = q2 * q3;
    q3q3 = q3 * q3;   
}

/*
 * Nonliner Exciplicit complementary filter (ECF), attitude estimator main function.
 *
 * @param argc number of commandline arguments (plus command name)
 * @param argv strings containing the arguments
 */
int unibo_att_esti_ECF_c_thread_main(int argc, char *argv[])
{
	const unsigned int loop_interval_alarm = 6500;	// loop interval in microseconds

	//! Time constant
	float dt = 0.005f;
	
	/* output euler angles */
	float euler[3] = {0.0f, 0.0f, 0.0f};
	
	/* Initialization */
	float Rot_matrix[9] = {1.f,  0.0f,  0.0f, 0.0f,  1.f,  0.0f, 0.0f,  0.0f,  1.f };		/**< init: identity matrix */
	float acc[3] = {0.0f, 0.0f, 0.0f};
	float gyro[3] = {0.0f, 0.0f, 0.0f};
	float estb[3] = {0.0f, 0.0f, 0.0f};
	float mag[3] = {0.0f, 0.0f, 0.0f};

	warnx("main thread started");

	struct sensor_combined_s raw;
	memset(&raw, 0, sizeof(raw));

	//! Initialize attitude vehicle uORB message.
	struct vehicle_attitude_s att;
	memset(&att, 0, sizeof(att));

	struct vehicle_control_mode_s control_mode;
	memset(&control_mode, 0, sizeof(control_mode));

	uint64_t last_data = 0;
	uint64_t last_measurement = 0;

	/* subscribe to raw data */
	int sub_raw = orb_subscribe(ORB_ID(sensor_combined));
	/* rate-limit raw data updates to 333 Hz (sensors app publishes at 200, so this is just paranoid) */
	orb_set_interval(sub_raw, 3);

	/* subscribe to param changes */
	int sub_params = orb_subscribe(ORB_ID(parameter_update));

	/* subscribe to control mode */
	int sub_control_mode = orb_subscribe(ORB_ID(vehicle_control_mode));

	/* advertise attitude */
	//orb_advert_t pub_att = orb_advertise(ORB_ID(vehicle_attitude), &att);
	//orb_advert_t att_pub = -1;
	orb_advert_t att_pub = orb_advertise(ORB_ID(vehicle_attitude), &att);

	int loopcounter = 0;
	int printcounter = 0;

	thread_running = true;

	float sensor_update_hz[3] = {0.0f, 0.0f, 0.0f};
	// XXX write this out to perf regs

	/* keep track of sensor updates */
	uint32_t sensor_last_count[3] = {0, 0, 0};
	uint64_t sensor_last_timestamp[3] = {0, 0, 0};

	struct unibo_att_esti_ECF_c_params so3_comp_params;
	struct unibo_att_esti_ECF_c_param_handles so3_comp_param_handles;

	/* initialize parameter handles */
	parameters_init(&so3_comp_param_handles);
	parameters_update(&so3_comp_param_handles, &so3_comp_params);

	uint64_t start_time = hrt_absolute_time();
	bool initialized = false;
	bool state_initialized = false;

	float gyro_offsets[3] = { 0.0f, 0.0f, 0.0f };
	unsigned offset_count = 0;

	/* register the perf counter */
	perf_counter_t so3_comp_loop_perf = perf_alloc(PC_ELAPSED, "unibo_att_esti_ECF_c");

	/*-----------------------------------------------
	 *                     Main loop
	 * ----------------------------------------------*/
	while (!thread_should_exit) {

		struct pollfd fds[2];
		fds[0].fd = sub_raw;
		fds[0].events = POLLIN;
		fds[1].fd = sub_params;
		fds[1].events = POLLIN;
		int ret = poll(fds, 2, 1000);

		if (ret < 0) {
			/* XXX this is seriously bad - should be an emergency */
		} else if (ret == 0) {
			/* check if we're in HIL - not getting sensor data is fine then */
			orb_copy(ORB_ID(vehicle_control_mode), sub_control_mode, &control_mode);

			if (!control_mode.flag_system_hil_enabled) {
				warnx("WARNING: Not getting sensors - sensor app running?");
			}
		} else {
			/* only update parameters if they changed */
			if (fds[1].revents & POLLIN) {
				/* read from param to clear updated flag */
				struct parameter_update_s update;
				orb_copy(ORB_ID(parameter_update), sub_params, &update);

				/* update parameters */
				parameters_update(&so3_comp_param_handles, &so3_comp_params);
			}

			/* only run filter if sensor values changed */
			if (fds[0].revents & POLLIN) {

				/* get latest measurements */
				orb_copy(ORB_ID(sensor_combined), sub_raw, &raw);

				if (!initialized) {

					gyro_offsets[0] += raw.gyro_rad_s[0];
					gyro_offsets[1] += raw.gyro_rad_s[1];
					gyro_offsets[2] += raw.gyro_rad_s[2];
					offset_count++;

					if (hrt_absolute_time() > start_time + 3000000l) {
						initialized = true;
						gyro_offsets[0] /= offset_count;
						gyro_offsets[1] /= offset_count;
						gyro_offsets[2] /= offset_count;
						warnx("gyro initialized, offsets: %.5f %.5f %.5f", gyro_offsets[0], gyro_offsets[1], gyro_offsets[2]);
					}

				} else {

					perf_begin(so3_comp_loop_perf);

					/* Calculate data time difference in seconds */
					dt = (raw.timestamp - last_measurement) / 1000000.0f;
					last_measurement = raw.timestamp;
					uint8_t update_vect[3] = {0, 0, 0};

					/* Fill in gyro measurements */
					if (sensor_last_timestamp[0] != raw.timestamp) {
						update_vect[0] = 1;
						sensor_update_hz[0] = 1e6f / (raw.timestamp - sensor_last_timestamp[0]);
						sensor_last_timestamp[0] = raw.timestamp;
					}

					gyro[0] = raw.gyro_rad_s[0] - gyro_offsets[0];
					gyro[1] = raw.gyro_rad_s[1] - gyro_offsets[1];
					gyro[2] = raw.gyro_rad_s[2] - gyro_offsets[2];

					/* update accelerometer measurements */
					if (sensor_last_timestamp[1] != raw.accelerometer_timestamp) {
						update_vect[1] = 1;
						sensor_update_hz[1] = 1e6f / (raw.timestamp - sensor_last_timestamp[1]);
						sensor_last_timestamp[1] = raw.accelerometer_timestamp;
					}

					acc[0] = raw.accelerometer_m_s2[0];
					acc[1] = raw.accelerometer_m_s2[1];
					acc[2] = raw.accelerometer_m_s2[2];

					/* update magnetometer measurements */
					if (sensor_last_timestamp[2] != raw.magnetometer_timestamp) {
						update_vect[2] = 1;
						sensor_update_hz[2] = 1e6f / (raw.timestamp - sensor_last_timestamp[2]);
						sensor_last_timestamp[2] = raw.magnetometer_timestamp;
					}

					mag[0] = raw.magnetometer_ga[0];
					mag[1] = raw.magnetometer_ga[1];
					mag[2] = raw.magnetometer_ga[2];

					/* initialize with good values once we have a reasonable dt estimate */
					if (!state_initialized && dt < 0.05f && dt > 0.001f) {
						state_initialized = true;
						warnx("state initialized");
					}

					/* do not execute the filter if not initialized */
					if (!state_initialized) {
						continue;
					}

					uint64_t timing_start = hrt_absolute_time();

					// NOTE : Accelerometer is reversed.
					// Because proper mount of PX4 will give you a reversed accelerometer readings.
					standardECFnew(gyro[0], gyro[1], gyro[2],
									estb[0], estb[1], estb[2],
										-acc[0], -acc[1], -acc[2],
										mag[0], mag[1], mag[2],
										so3_comp_params.K1,
										so3_comp_params.K2,
										so3_comp_params.K3,
										so3_comp_params.K4,
										so3_comp_params.Kb,
										so3_comp_params.SAT,
										dt);

					// direction cosine matrix of 1-2-3 sequence
					// Resulted Rotation matrix convert from Inertial frame to body frame
					Rot_matrix[0] = q0q0 + q1q1 - q2q2 - q3q3;	// R11
					Rot_matrix[1] = 2.f * (q1*q2 + q0*q3);		// R12
					Rot_matrix[2] = 2.f * (q1*q3 - q0*q2);		// R13
					Rot_matrix[3] = 2.f * (q1*q2 - q0*q3);		// R21
					Rot_matrix[4] = q0q0 - q1q1 + q2q2 - q3q3;	// R22
					Rot_matrix[5] = 2.f * (q2*q3 + q0*q1);		// R23
					Rot_matrix[6] = 2.f * (q1*q3 + q0*q2);		// R31
					Rot_matrix[7] = 2.f * (q2*q3 - q0*q1);		// R32
					Rot_matrix[8] = q0q0 - q1q1 - q2q2 + q3q3;	// R33

					// Euler Angles using Unit Quaternions;

					euler[0]= atan2f((2.0f*(q2q3+q0q1)),1.0f-2.0f*(q1q1+q2q2));		// Roll
					euler[1]= asinf(-2.0f*(q1q3-q0q2));								// Pitch
					euler[2]= atan2f((2.0f*(q1q2+q0q3)),1.0f-2.0f*(q2q2+q3q3));		// Yaw
					
					/* swap values for next iteration, check for fatal inputs */
					if (isfinite(euler[0]) && isfinite(euler[1]) && isfinite(euler[2])) {
						// Publish only finite euler angles
						att.roll = euler[0] - so3_comp_params.roll_off;
						att.pitch = euler[1] - so3_comp_params.pitch_off;
						att.yaw = euler[2] - so3_comp_params.yaw_off;
					} else {
						/* due to inputs or numerical failure the output is invalid, skip it */
						// Due to inputs or numerical failure the output is invalid
						warnx("infinite euler angles, rotation matrix:");
						warnx("%.3f %.3f %.3f", Rot_matrix[0], Rot_matrix[1], Rot_matrix[2]);
						warnx("%.3f %.3f %.3f", Rot_matrix[3], Rot_matrix[4], Rot_matrix[5]);
						warnx("%.3f %.3f %.3f", Rot_matrix[6], Rot_matrix[7], Rot_matrix[8]);
						// Don't publish anything
						continue;
					}

					if (last_data > 0 && raw.timestamp > last_data + 12000) {
						warnx("sensor data missed");
					}

					last_data = raw.timestamp;

					/* send out */
					att.timestamp = raw.timestamp;
					
					// Quaternion
					att.q[0] = q0;
					att.q[1] = q1;
					att.q[2] = q2;
					att.q[3] = q3;
					att.q_valid = true;

					// Euler angle rate. But it needs to be investigated again.
					/*
					att.rollspeed = 2.0f*(-q1*dq0 + q0*dq1 - q3*dq2 + q2*dq3);
					att.pitchspeed = 2.0f*(-q2*dq0 + q3*dq1 + q0*dq2 - q1*dq3);
					att.yawspeed = 2.0f*(-q3*dq0 -q2*dq1 + q1*dq2 + q0*dq3);
					*/
					att.rollspeed = gyro[0];
					att.pitchspeed = gyro[1];
					att.yawspeed = gyro[2];

					att.rollacc = 0;
					att.pitchacc = 0;
					att.yawacc = 0;

					/* TODO: Bias estimation required */
					memcpy(&att.rate_offsets, &(gyro_bias), sizeof(att.rate_offsets));

					/* copy rotation matrix */
					memcpy(&att.R, Rot_matrix, sizeof(float)*9);
					att.R_valid = true;
					
					// Publish
					if (att_pub > 0) {
						orb_publish(ORB_ID(vehicle_attitude), att_pub, &att);
					} else {
						warnx("NaN in roll/pitch/yaw estimate!");
						 orb_advertise(ORB_ID(vehicle_attitude), &att);
					}

					perf_end(so3_comp_loop_perf);
				}
			}
		}

		loopcounter++;
	}
// here the main loop stop

	thread_running = false;

	return 0;
}
