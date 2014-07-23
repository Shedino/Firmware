export EXTRADEFINES := $(EXTRADEFINES) -DRT -I$(PX4_MODULE_SRC)lib/matlab
# -I$(MODULE_WORK_DIR)libraries -I$(MODULE_WORK_DIR)include
#INCLUDE_DIRS		+= $(MODULE_WORK_DIR)libraries
CFLAGS				+= -I$(MODULE_SRC)include -I$(MODULE_SRC)codegen

MODULE_COMMAND		= 	ahrs_SO3_unibo

SRCS				= 	ahrs_SO3_unibo.c \
						Infrastructure/codegen_call.c \
			   			codegen/ahrs_so3_unibo_data.c \
			   			codegen/ahrs_so3_unibo.c \
			   			codegen/rt_nonfinite.c \
			   			codegen/rtGetInf.c \
			   			codegen/rtGetNaN.c
			   	

			   			#codegen/fixedpoint.c \
			   			#codegen/rtw_modelmap_utils.c \
			   			#codegen/rt_logging_mmi.c \
			   			#codegen/rt_logging.c \
			   			
			   			