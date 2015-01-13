export EXTRADEFINES := $(EXTRADEFINES) -DRT -DIRIS -I$(PX4_MODULE_SRC)lib/matlab
# -I$(MODULE_WORK_DIR)libraries -I$(MODULE_WORK_DIR)include
#INCLUDE_DIRS		+= $(MODULE_WORK_DIR)libraries
CFLAGS				+= -I$(MODULE_SRC)include -I$(MODULE_SRC)LowLevel

MODULE_COMMAND		= 	unibo_ESC32_reader

SRCS				= 	unibo_ESC32_reader.c 
			   			
			   			