/****************************************************************************
 *
 *   Copyright (C) 2013 PX4 Development Team. All rights reserved.
 *   Author: Mohammad R. M. Hayajneh <hayajneh09@gmail.com>
 *           						<mohammad.hayajneh3@unibo.it>
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

/*/* @file unibo_att_esti_ECF_c_params.c
 * University of Bologna_ CASY Lab
 *
 * Parameters for nonlinear Exciplicet complementary filter (ECF) .
 */

#include "unibo_att_esti_ECF_c_params.h"

/* This file contains the gains of filter (ECF)
 * ----------------------------------------------
 *              A Guide for Gain Tuning
 *-----------------------------------------------
 *//* The current gains have default values, insure the stabilty for the vehicle.
 *//*
 *//* The Proportional gains ((k1 and k2)) chosen to manage between the lowpass filter
 *//* of the Accelerometer and Magnetometer measurments and the highpass filter of the
 *//* attitude measurments of the integrated gyro.
 *//* the Gain ((SAT)) for saturation
 *//* the gain kb is resposible about the desaturation rate
 *//*
 *//* chose always k2 < k1, k2 about 5 times smaller the k1.
 *//* try to keep k1/k3 = k2/k4;
 *//* chose kb large number in order to obtain a fast desaturation rate of estimated bias
 */
PARAM_DEFINE_FLOAT(SO3_COMP_K1, 5.0f);


PARAM_DEFINE_FLOAT(SO3_COMP_K2, 1.0f);


PARAM_DEFINE_FLOAT(SO3_COMP_K3, 0.02f);
PARAM_DEFINE_FLOAT(SO3_COMP_K4, 0.016f);
PARAM_DEFINE_FLOAT(SO3_COMP_Kb, 16.0f);
PARAM_DEFINE_FLOAT(SO3_COMP_SAT, 0.03f);

/* offsets in roll, pitch and yaw of sensor plane and body */
PARAM_DEFINE_FLOAT(SO3_ROLL_OFFS, 0.0f);
PARAM_DEFINE_FLOAT(SO3_PITCH_OFFS, 0.0f);
PARAM_DEFINE_FLOAT(SO3_YAW_OFFS, 0.0f);

int parameters_init(struct unibo_att_esti_ECF_c_param_handles *h)
{

	/* sensors gain parameters */
	h->K1 = 	param_find("SO3_COMP_K1");
	h->K2 = 	param_find("SO3_COMP_K2");

	/* Filter gain parameters */
	h->K3 = 	param_find("SO3_COMP_K3");
	h->K4 = 	param_find("SO3_COMP_K4");
	h->Kb = 	param_find("SO3_COMP_Kb");
	h->SAT = 	param_find("SO3_COMP_SAT");


	/* Attitude offset (WARNING: Do not change if you do not know what exactly this variable wil lchange) */
	h->roll_off  =	param_find("SO3_ROLL_OFFS");
	h->pitch_off =	param_find("SO3_PITCH_OFFS");
	h->yaw_off   =	param_find("SO3_YAW_OFFS");

	return OK;
}

int parameters_update(const struct unibo_att_esti_ECF_c_param_handles *h, struct unibo_att_esti_ECF_c_params *p)
{
	/* Update filter gain */
	param_get(h->K1, &(p->K1));
	param_get(h->K2, &(p->K2));
	param_get(h->K3, &(p->K3));
	param_get(h->K4, &(p->K4));
	param_get(h->Kb, &(p->Kb));
	param_get(h->SAT, &(p->SAT));

	/* Update attitude offset */
	param_get(h->roll_off, &(p->roll_off));
	param_get(h->pitch_off, &(p->pitch_off));
	param_get(h->yaw_off, &(p->yaw_off));

	return OK;
}
