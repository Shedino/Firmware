#ifndef MR_CONFIG_STRUCT_H
#define MR_CONFIG_STRUCT_H

struct mr_config_struct
{
   int radius[6];
   int height[6];
   int azimut[6];
   int mass[6];
   int direction[6];
   int operating[6];
   int thrust[6];
   int torque[6];
};
#endif