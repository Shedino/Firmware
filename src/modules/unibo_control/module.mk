export EXTRADEFINES := $(EXTRADEFINES) -DRT 
# -I$(MODULE_WORK_DIR)libraries -I$(MODULE_WORK_DIR)include
#INCLUDE_DIRS		+= $(MODULE_WORK_DIR)libraries
CFLAGS				+= -I$(MODULE_WORK_DIR)libraries


MODULE_COMMAND		= 	unibo_control

SRCS				= 	unibo_control.c \
			   			main_procedures.c \
			   			Infrastructure/CInputs.c \
			   			Infrastructure/Low_Level_Free_Flight_Control.c \
			   			PacketACK.c \
			   			PacketOFLOW.c \
			   			PacketOPTITRACK.c \
			   			PacketPARAMETERS.c \
			   			PacketREFERENCES.c \
			   			PacketSTATE.c \
			   			PacketTELEMETRY.c \
			   			LowLevel/Model_GS_data.c \
			   			LowLevel/Model_GS.c \
			   			LowLevel/fixedpoint.c \
			   			LowLevel/rt_nonfinite.c \
			   			LowLevel/rtGetInf.c \
			   			LowLevel/rtGetNaN.c \
			   			LowLevel/rtw_modelmap_utils.c \
			   			utils.c 

			   			#LowLevel/rt_logging_mmi.c \
			   			#LowLevel/rt_logging.c \
			   			
			   			