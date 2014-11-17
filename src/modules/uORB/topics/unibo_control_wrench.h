/*
 *
 * Filename: unibo_control_wrench.h
 * Authors: Melega Marco
 *
 * Description:
 * Unibo control wrench vector topic to store the control wrench vector produced by
 * the control law and taken as input in the allocation algorithm
 */

#ifndef UNIBO_CONTROL_WRENCH_H_
#define UNIBO_CONTROL_WRENCH_H_


#include "../uORB.h"


struct unibo_control_wrench_s
{
	float force[3];
	float torque[3];
};

/* register this as object request broker structure */
ORB_DECLARE(unibo_control_wrench);

#endif /* UNIBO_CONTROL_WRENCH_H_ */
