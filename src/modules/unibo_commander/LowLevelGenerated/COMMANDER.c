/*
 * COMMANDER.c
 *
 * Code generation for model "COMMANDER".
 *
 * Model version              : 1.2466
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Wed Sep 03 11:51:27 2014
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#include "COMMANDER.h"
#include "COMMANDER_private.h"

/* Block states (auto storage) */
D_Work_COMMANDER COMMANDER_DWork;

/* External inputs (root inport signals with auto storage) */
ExternalInputs_COMMANDER COMMANDER_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_COMMANDER COMMANDER_Y;

/* Real-time model */
RT_MODEL_COMMANDER COMMANDER_M_;
RT_MODEL_COMMANDER *const COMMANDER_M = &COMMANDER_M_;

/* Model output function */
static void COMMANDER_output(void)
{
  /* MATLAB Function: '<S2>/Embedded MATLAB Function' incorporates:
   *  Inport: '<Root>/ARMED'
   *  Inport: '<Root>/ATTITUDE_VALID'
   *  Inport: '<Root>/BUTTON'
   *  Inport: '<Root>/LOC_POS_VALID'
   *  Inport: '<Root>/NO_XBEE'
   *  Memory: '<S2>/Initial State'
   *  SignalConversion: '<S3>/TmpSignal ConversionAt SFunction Inport1'
   */
  /* MATLAB Function 'FLIGHT MODE COMMANDER/LOW LEVEL SUPERVISOR/Embedded MATLAB Function': '<S3>:1' */
  /* States */
  /* '<S3>:1:4' */
  /* '<S3>:1:5' */
  /* '<S3>:1:6' */
  /* '<S3>:1:7' */
  /* '<S3>:1:8' */
  /* '<S3>:1:9' */
  /* '<S3>:1:10' */
  /* '<S3>:1:11' */
  /* Buttons */
  /* '<S3>:1:14' */
  /* TASTO 3 JOYSTICK */
  /* '<S3>:1:15' */
  /* TASTO 8 JOYSTICK */
  /* '<S3>:1:16' */
  /* TASTO 5+7 JOYSTICK */
  /* '<S3>:1:17' */
  /* TASTO 6+8 JOYSTICK */
  /* '<S3>:1:18' */
  /* TASTO 5+6 JOYSTICK */
  /* '<S3>:1:19' */
  /* TASTO 8+7 JOYSTICK */
  /* Events */
  /*  1 = no_xbee */
  /*  2 = attitude_valid */
  /*  3 = loc_pos_valid */
  /*  4 = armed */
  /* '<S3>:1:28' */
  switch (COMMANDER_DWork.InitialState_PreviousInput) {
   case 0:
    /* Outport: '<Root>/STATE' */
    /* -----------STOP------------- */
    /* '<S3>:1:30' */
    COMMANDER_Y.STATE = 0;
    if (COMMANDER_U.NO_XBEE) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:31' */
      /* xbee lost */
      /* '<S3>:1:32' */
      COMMANDER_Y.STATE = 60;
    } else {
      if (COMMANDER_U.ARMED && (COMMANDER_U.BUTTON == 128U)) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:35' */
        /* armed and pre button */
        /* '<S3>:1:36' */
        COMMANDER_Y.STATE = 10;
      }
    }
    break;

   case 10:
    /* Outport: '<Root>/STATE' */
    /* -----------PREFLIGHT------------- */
    /* '<S3>:1:41' */
    COMMANDER_Y.STATE = 10;
    if (COMMANDER_U.NO_XBEE) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:42' */
      /* xbee lost */
      /* '<S3>:1:43' */
      COMMANDER_Y.STATE = 60;
    } else if (COMMANDER_U.BUTTON == 4U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:46' */
      /* STOP!! */
      /* '<S3>:1:47' */
      COMMANDER_Y.STATE = 0;
    } else if ((COMMANDER_U.BUTTON == 80U) && COMMANDER_U.ATTITUDE_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:50' */
      /* '<S3>:1:51' */
      COMMANDER_Y.STATE = 20;
    } else if ((COMMANDER_U.BUTTON == 160U) && COMMANDER_U.ATTITUDE_VALID &&
               COMMANDER_U.LOC_POS_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:54' */
      /* '<S3>:1:55' */
      COMMANDER_Y.STATE = 30;
    } else if ((COMMANDER_U.BUTTON == 48U) && COMMANDER_U.ATTITUDE_VALID &&
               COMMANDER_U.LOC_POS_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:58' */
      /* '<S3>:1:59' */
      COMMANDER_Y.STATE = 40;
    } else {
      if ((COMMANDER_U.BUTTON == 192U) && COMMANDER_U.ATTITUDE_VALID &&
          COMMANDER_U.LOC_POS_VALID) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:62' */
        /* '<S3>:1:63' */
        COMMANDER_Y.STATE = 50;
      }
    }
    break;

   case 20:
    /* Outport: '<Root>/STATE' */
    /* -----------ATTITUDE & THRUST------------- */
    /* '<S3>:1:68' */
    COMMANDER_Y.STATE = 20;
    if (COMMANDER_U.NO_XBEE) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:69' */
      /* xbee lost */
      /* '<S3>:1:70' */
      COMMANDER_Y.STATE = 60;
    } else if (COMMANDER_U.BUTTON == 4U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:73' */
      /* STOP!! */
      /* '<S3>:1:74' */
      COMMANDER_Y.STATE = 0;
    } else if ((COMMANDER_U.BUTTON == 160U) && COMMANDER_U.LOC_POS_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:77' */
      /* '<S3>:1:78' */
      COMMANDER_Y.STATE = 30;
    } else if ((COMMANDER_U.BUTTON == 48U) && COMMANDER_U.LOC_POS_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:81' */
      /* '<S3>:1:82' */
      COMMANDER_Y.STATE = 40;
    } else {
      if ((COMMANDER_U.BUTTON == 192U) && COMMANDER_U.LOC_POS_VALID) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:85' */
        /* '<S3>:1:86' */
        COMMANDER_Y.STATE = 50;
      }
    }
    break;

   case 30:
    /* Outport: '<Root>/STATE' */
    /* -----------AUTO LOW LEVEL------------- */
    /* '<S3>:1:91' */
    COMMANDER_Y.STATE = 30;
    if (COMMANDER_U.NO_XBEE) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:92' */
      /* xbee lost */
      /* '<S3>:1:93' */
      COMMANDER_Y.STATE = 60;
    } else if (COMMANDER_U.BUTTON == 4U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:96' */
      /* STOP!! */
      /* '<S3>:1:97' */
      COMMANDER_Y.STATE = 0;
    } else if (COMMANDER_U.BUTTON == 48U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:100' */
      /* '<S3>:1:101' */
      COMMANDER_Y.STATE = 40;
    } else if (COMMANDER_U.BUTTON == 192U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:104' */
      /* '<S3>:1:105' */
      COMMANDER_Y.STATE = 50;
    } else {
      if ((COMMANDER_U.BUTTON == 80U) || (!COMMANDER_U.LOC_POS_VALID)) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:108' */
        /* '<S3>:1:109' */
        COMMANDER_Y.STATE = 20;
      }
    }
    break;

   case 40:
    /* Outport: '<Root>/STATE' */
    /* -----------AUTO HIGH LEVEL------------- */
    /* '<S3>:1:114' */
    COMMANDER_Y.STATE = 40;
    if (COMMANDER_U.NO_XBEE) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:115' */
      /* xbee lost */
      /* '<S3>:1:116' */
      COMMANDER_Y.STATE = 60;
    } else if (COMMANDER_U.BUTTON == 4U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:119' */
      /* STOP!! */
      /* '<S3>:1:120' */
      COMMANDER_Y.STATE = 0;
    } else if (COMMANDER_U.BUTTON == 160U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:123' */
      /* '<S3>:1:124' */
      COMMANDER_Y.STATE = 30;
    } else if (COMMANDER_U.BUTTON == 192U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:127' */
      /* '<S3>:1:128' */
      COMMANDER_Y.STATE = 50;
    } else {
      if ((COMMANDER_U.BUTTON == 80U) || (!COMMANDER_U.LOC_POS_VALID)) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:131' */
        /* '<S3>:1:132' */
        COMMANDER_Y.STATE = 20;
      }
    }
    break;

   case 50:
    /* Outport: '<Root>/STATE' */
    /* -----------AUTO WAYPOINT------------- */
    /* '<S3>:1:137' */
    COMMANDER_Y.STATE = 50;
    if (COMMANDER_U.NO_XBEE) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:138' */
      /* xbee lost */
      /* '<S3>:1:139' */
      COMMANDER_Y.STATE = 60;
    } else if (COMMANDER_U.BUTTON == 4U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:142' */
      /* STOP!! */
      /* '<S3>:1:143' */
      COMMANDER_Y.STATE = 0;
    } else if (COMMANDER_U.BUTTON == 160U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:146' */
      /* '<S3>:1:147' */
      COMMANDER_Y.STATE = 30;
    } else if (COMMANDER_U.BUTTON == 48U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:150' */
      /* '<S3>:1:151' */
      COMMANDER_Y.STATE = 40;
    } else {
      if ((COMMANDER_U.BUTTON == 80U) || (!COMMANDER_U.LOC_POS_VALID)) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:154' */
        /* '<S3>:1:155' */
        COMMANDER_Y.STATE = 20;
      }
    }
    break;

   case 60:
    /* Outport: '<Root>/STATE' */
    /* -----------COMMUNICATION LOST------------- */
    /* '<S3>:1:160' */
    COMMANDER_Y.STATE = 60;
    break;

   default:
    /* Outport: '<Root>/STATE' */
    /* '<S3>:1:163' */
    COMMANDER_Y.STATE = 1000;
    break;
  }

  /* End of MATLAB Function: '<S2>/Embedded MATLAB Function' */
}

/* Model update function */
static void COMMANDER_update(void)
{
  /* Update for Memory: '<S2>/Initial State' */
  COMMANDER_DWork.InitialState_PreviousInput = COMMANDER_Y.STATE;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++COMMANDER_M->Timing.clockTick0)) {
    ++COMMANDER_M->Timing.clockTickH0;
  }

  COMMANDER_M->Timing.t[0] = COMMANDER_M->Timing.clockTick0 *
    COMMANDER_M->Timing.stepSize0 + COMMANDER_M->Timing.clockTickH0 *
    COMMANDER_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void COMMANDER_initialize(void)
{
  /* InitializeConditions for Memory: '<S2>/Initial State' */
  COMMANDER_DWork.InitialState_PreviousInput = 0;
}

/* Model terminate function */
void COMMANDER_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  COMMANDER_output();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  COMMANDER_update();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  COMMANDER_initialize();
}

void MdlTerminate(void)
{
  COMMANDER_terminate();
}

RT_MODEL_COMMANDER *COMMANDER(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)COMMANDER_M, 0,
                sizeof(RT_MODEL_COMMANDER));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = COMMANDER_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    COMMANDER_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    COMMANDER_M->Timing.sampleTimes = (&COMMANDER_M->Timing.sampleTimesArray[0]);
    COMMANDER_M->Timing.offsetTimes = (&COMMANDER_M->Timing.offsetTimesArray[0]);

    /* task periods */
    COMMANDER_M->Timing.sampleTimes[0] = (0.01);

    /* task offsets */
    COMMANDER_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(COMMANDER_M, &COMMANDER_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = COMMANDER_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    COMMANDER_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(COMMANDER_M, -1);
  COMMANDER_M->Timing.stepSize0 = 0.01;
  COMMANDER_M->solverInfoPtr = (&COMMANDER_M->solverInfo);
  COMMANDER_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&COMMANDER_M->solverInfo, 0.01);
  rtsiSetSolverMode(&COMMANDER_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* states (dwork) */
  COMMANDER_M->Work.dwork = ((void *) &COMMANDER_DWork);
  (void) memset((void *)&COMMANDER_DWork, 0,
                sizeof(D_Work_COMMANDER));

  /* external inputs */
  COMMANDER_M->ModelData.inputs = (((void*)&COMMANDER_U));
  (void) memset((void *)&COMMANDER_U, 0,
                sizeof(ExternalInputs_COMMANDER));

  /* external outputs */
  COMMANDER_M->ModelData.outputs = (&COMMANDER_Y);
  COMMANDER_Y.STATE = 0;

  /* Initialize Sizes */
  COMMANDER_M->Sizes.numContStates = (0);/* Number of continuous states */
  COMMANDER_M->Sizes.numY = (1);       /* Number of model outputs */
  COMMANDER_M->Sizes.numU = (5);       /* Number of model inputs */
  COMMANDER_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  COMMANDER_M->Sizes.numSampTimes = (1);/* Number of sample times */
  COMMANDER_M->Sizes.numBlocks = (5);  /* Number of blocks */
  COMMANDER_M->Sizes.numBlockIO = (1); /* Number of block outputs */
  return COMMANDER_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
