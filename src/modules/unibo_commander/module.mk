export EXTRADEFINES := $(EXTRADEFINES) -DRT -I$(PX4_MODULE_SRC)lib/matlab
# -I$(MODULE_WORK_DIR)libraries -I$(MODULE_WORK_DIR)include
#INCLUDE_DIRS		+= $(MODULE_WORK_DIR)libraries
CFLAGS				+= -I$(MODULE_SRC)include -I$(MODULE_SRC)LowLevelGenerated

MODULE_COMMAND		= 	unibo_commander

SRCS				= 	unibo_commander.c \
			   			Infrastructure/Low_level_commander.c \
			   			LowLevelGenerated/COMMANDER.c \
			   			LowLevelGenerated/rt_nonfinite.c \
			   			LowLevelGenerated/rtGetInf.c \
			   			LowLevelGenerated/rtGetNaN.c 

			   			
			   			