export EXTRADEFINES := $(EXTRADEFINES) -DRT -I$(PX4_MODULE_SRC)lib/matlab
# -I$(MODULE_WORK_DIR)libraries -I$(MODULE_WORK_DIR)include
#INCLUDE_DIRS		+= $(MODULE_WORK_DIR)libraries
CFLAGS				+= -I$(MODULE_SRC)include -I$(MODULE_SRC)LowLevelGenerated

MODULE_COMMAND		= 	unibo_trajectory_ref

SRCS				= 	unibo_trajectory_ref.c \
			   			Infrastructure/Low_Level_Trajectory.c \
			   			LowLevelGenerated/TRAJECTORY_GENERATOR_APP.c \
			   			LowLevelGenerated/rt_nonfinite.c \
			   			LowLevelGenerated/rtGetInf.c \
			   			LowLevelGenerated/rtGetNaN.c 

			   			
			   			