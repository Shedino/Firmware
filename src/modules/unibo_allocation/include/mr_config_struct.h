#ifndef MR_CONFIG_STRUCT_H
#define MR_CONFIG_STRUCT_H

#include <init_alloc_var.h>

struct mr_config_struct
{
	unsigned int rotors_number;
	unsigned int radius[MAXROT];
	unsigned int diameter[MAXROT];
	int height[MAXROT];
	int azimut[MAXROT];
	int mass[MAXROT];
	int direction[MAXROT];
	int operating[MAXROT];
	float thrust[MAXROT];
	int torque[MAXROT];
};
#endif
