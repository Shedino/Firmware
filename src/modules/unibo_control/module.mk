MODULE_COMMAND		= 	unibo_control

SRCS				= 	unibo_control.c \
			   			main_procedures.cpp \
			   			LowLevel/Model_GS_data.c \
			   			LowLevel/Model_GS.c \
			   			LowLevel/rt_nonfinite.c \
			   			LowLevel/rtGetInf.c \
			   			LowLevel/rtGetNaN.c \
			   			Infrastructure/CInputs.cpp \
			   			Infrastructure/Low_Level_Free_Flight_Control.cpp \
			   			PacketACK.cpp \
			   			PacketIMU.cpp \
			   			PacketOFLOW.cpp \
			   			PacketOPTITRACK.cpp \
			   			PacketPARAMETERS.cpp \
			   			PacketREFERENCES.cpp \
			   			PacketSTATE.cpp \
			   			PacketTELEMETRY.cpp \
			   			utils.cpp
