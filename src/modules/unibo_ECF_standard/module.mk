export EXTRADEFINES := $(EXTRADEFINES) -DRT -I$(PX4_MODULE_SRC)lib/matlab
# -I$(MODULE_WORK_DIR)libraries -I$(MODULE_WORK_DIR)include
#INCLUDE_DIRS		+= $(MODULE_WORK_DIR)libraries
CFLAGS				+= -I$(MODULE_SRC)include -I$(MODULE_SRC)ECF_codgen

MODULE_COMMAND		= 	unibo_ECF_standard

SRCS				= 	unibo_ECF_standard.c \
			   			Infrastructure/Low_Level_Free_Flight_Control.c \
			   			ECF_codgen/ECF_stand_q_data.c \
			   			ECF_codgen/ECF_stand_q.c \
			   			ECF_codgen/rt_nonfinite.c \
			   			ECF_codgen/rtGetInf.c \
			   			ECF_codgen/rtGetNaN.c 
			   			
			   			#utils.c 

			   			#LowLevel/fixedpoint.c \
			   			#LowLevel/rtw_modelmap_utils.c \
			   			#LowLevel/rt_logging_mmi.c \
			   			#LowLevel/rt_logging.c \
			   			
			   			