#export EXTRADEFINES := $(EXTRADEFINES) -DRT 
#CFLAGS				+= -I$(MODULE_WORK_DIR)libraries
INCLUDE_DIRS	    += $(MAVLINK_SRC)/include/mavlink
#CFLAGS				+= -I$(MODULE_SRC)mavlink

MODULE_COMMAND		= 	unibo_mavlink

SRCS				= 	unibo_mavlink.c
			   			
			   			