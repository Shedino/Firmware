export EXTRADEFINES := $(EXTRADEFINES) -DRT -I$(PX4_MODULE_SRC)lib/matlab
# -I$(PX4_MODULE_SRC)modules/unibo_allocation
# -I$(MODULE_WORK_DIR)libraries -I$(MODULE_WORK_DIR)include
#INCLUDE_DIRS		+= $(MODULE_WORK_DIR)libraries
CFLAGS				+= -I$(MODULE_SRC)include -I$(MODULE_SRC)LowLevelGenerated

MODULE_COMMAND		= 	unibo_configuration

SRCS				= 	unibo_configuration.c 