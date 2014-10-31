export EXTRADEFINES := $(EXTRADEFINES) -DRT -DIRIS -I$(PX4_MODULE_SRC)lib/matlab
# -I$(MODULE_WORK_DIR)libraries -I$(MODULE_WORK_DIR)include
#INCLUDE_DIRS		+= $(MODULE_WORK_DIR)libraries
CFLAGS				+= -I$(MODULE_SRC)include -I$(MODULE_SRC)LowLevel

MODULE_COMMAND		= 	unibo_control

SRCS				= 	unibo_control.c \
			   			main_procedures.c \
			   			Infrastructure/Low_Level_Free_Flight_Control.c \
			   			LowLevel/Model_GS.c \
			   			LowLevel/rt_nonfinite.c \
			   			LowLevel/rtGetInf.c \
			   			LowLevel/rtGetNaN.c \
			   			utils.c 
						
						#Infrastructure/CInputs.c \
						#LowLevel/Model_GS_data.c \
			   			#LowLevel/fixedpoint.c \
			   			#LowLevel/rtw_modelmap_utils.c \
			   			#LowLevel/rt_logging_mmi.c \
			   			#LowLevel/rt_logging.c \
			   			
			   			