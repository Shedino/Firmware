/*
 * COMMANDER.c
 *
 * Code generation for model "COMMANDER".
 *
 * Model version              : 1.2481
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Fri Oct 24 18:12:44 2014
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
   *  Inport: '<Root>/CMD_LANDING'
   *  Inport: '<Root>/CMD_TAKE_OFF'
   *  Inport: '<Root>/LANDED'
   *  Inport: '<Root>/LOC_XY_VALID'
   *  Inport: '<Root>/LOC_Z_VALID'
   *  Inport: '<Root>/NO_XBEE'
   *  Inport: '<Root>/TOOK_OFF'
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
  /* '<S3>:1:12' */
  /* '<S3>:1:13' */
  /* '<S3>:1:14' */
  /* '<S3>:1:15' */
  /* Buttons */
  /* '<S3>:1:18' */
  /* TASTO 3 JOYSTICK */
  /* '<S3>:1:19' */
  /* TASTO 8 JOYSTICK */
  /* '<S3>:1:20' */
  /* TASTO 5+7 JOYSTICK */
  /* '<S3>:1:21' */
  /* TASTO 6+8 JOYSTICK */
  /* '<S3>:1:22' */
  /* TASTO 5+6 JOYSTICK */
  /* '<S3>:1:23' */
  /* TASTO 8+7 JOYSTICK */
  /* Events index */
  /* '<S3>:1:37' */
  switch (COMMANDER_DWork.InitialState_PreviousInput) {
   case 0:
    /* Outport: '<Root>/STATE' */
    /* -----------STOP------------- */
    /* '<S3>:1:39' */
    COMMANDER_Y.STATE = 0;
    if (COMMANDER_U.NO_XBEE) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:40' */
      /* xbee lost */
      /* '<S3>:1:41' */
      COMMANDER_Y.STATE = 0;
    } else {
      if (COMMANDER_U.ARMED && (COMMANDER_U.BUTTON == 128U)) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:44' */
        /* armed and pre button */
        /* '<S3>:1:45' */
        COMMANDER_Y.STATE = 10;
      }
    }
    break;

   case 10:
    /* Outport: '<Root>/STATE' */
    /* -----------PREFLIGHT------------- */
    /* '<S3>:1:50' */
    COMMANDER_Y.STATE = 10;
    if (COMMANDER_U.NO_XBEE) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:51' */
      /* xbee lost */
      /* '<S3>:1:52' */
      COMMANDER_Y.STATE = 0;
    } else if (COMMANDER_U.BUTTON == 4U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:55' */
      /* STOP!! */
      /* '<S3>:1:56' */
      COMMANDER_Y.STATE = 0;
    } else if ((COMMANDER_U.BUTTON == 80U) && COMMANDER_U.ATTITUDE_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:59' */
      /* '<S3>:1:60' */
      COMMANDER_Y.STATE = 20;
    } else if ((COMMANDER_U.BUTTON == 160U) && COMMANDER_U.ATTITUDE_VALID &&
               COMMANDER_U.LOC_XY_VALID && COMMANDER_U.LOC_Z_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:63' */
      /* '<S3>:1:64' */
      COMMANDER_Y.STATE = 30;
    } else if ((COMMANDER_U.BUTTON == 48U) && COMMANDER_U.ATTITUDE_VALID &&
               COMMANDER_U.LOC_XY_VALID && COMMANDER_U.LOC_Z_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:67' */
      /* '<S3>:1:68' */
      COMMANDER_Y.STATE = 40;
    } else {
      if ((COMMANDER_U.BUTTON == 192U) && COMMANDER_U.ATTITUDE_VALID &&
          COMMANDER_U.LOC_XY_VALID && COMMANDER_U.LOC_Z_VALID) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:71' */
        /* '<S3>:1:72' */
        COMMANDER_Y.STATE = 50;
      }
    }
    break;

   case 20:
    /* Outport: '<Root>/STATE' */
    /* -----------ATTITUDE & THRUST------------- */
    /* '<S3>:1:77' */
    COMMANDER_Y.STATE = 20;
    if (COMMANDER_U.NO_XBEE) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:78' */
      /* xbee lost */
      /*              if (events(loc_xy_valid) && events(loc_z_valid)) */
      /*                  state_out = LAND; */
      /*                  break; */
      /*              elseif (events(loc_z_valid)) */
      /*                  state_out = Z_LAND; */
      /*                  break; */
      /*              else */
      /*                  state_out = U_LAND; */
      /*                  break; */
      /*              end */
      /* '<S3>:1:89' */
      COMMANDER_Y.STATE = 70;
    } else if (COMMANDER_U.BUTTON == 4U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:92' */
      /* STOP!! */
      /* '<S3>:1:93' */
      COMMANDER_Y.STATE = 0;
    } else if ((COMMANDER_U.BUTTON == 160U) && COMMANDER_U.LOC_XY_VALID &&
               COMMANDER_U.LOC_Z_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:96' */
      /* '<S3>:1:97' */
      COMMANDER_Y.STATE = 30;
    } else if ((COMMANDER_U.BUTTON == 48U) && COMMANDER_U.LOC_XY_VALID &&
               COMMANDER_U.LOC_Z_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:100' */
      /* '<S3>:1:101' */
      COMMANDER_Y.STATE = 40;
    } else {
      if ((COMMANDER_U.BUTTON == 192U) && COMMANDER_U.LOC_XY_VALID &&
          COMMANDER_U.LOC_Z_VALID) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:104' */
        /* '<S3>:1:105' */
        COMMANDER_Y.STATE = 50;
      }
    }
    break;

   case 30:
    /* Outport: '<Root>/STATE' */
    /* -----------AUTO LOW LEVEL------------- */
    /* '<S3>:1:110' */
    COMMANDER_Y.STATE = 30;
    if (COMMANDER_U.NO_XBEE) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:111' */
      /* xbee lost */
      /*              if (events(loc_xy_valid) && events(loc_z_valid)) */
      /*                  state_out = LAND; */
      /*                  break; */
      /*              elseif (events(loc_z_valid)) */
      /*                  state_out = Z_LAND; */
      /*                  break; */
      /*              else */
      /*                  state_out = U_LAND; */
      /*                  break; */
      /*              end */
      /* '<S3>:1:122' */
      COMMANDER_Y.STATE = 70;
    } else if ((!COMMANDER_U.LOC_XY_VALID) && COMMANDER_U.LOC_Z_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:125' */
      /* '<S3>:1:126' */
      COMMANDER_Y.STATE = 80;
    } else if ((!COMMANDER_U.LOC_XY_VALID) && (!COMMANDER_U.LOC_Z_VALID)) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:129' */
      /* '<S3>:1:130' */
      COMMANDER_Y.STATE = 70;
    } else if (COMMANDER_U.BUTTON == 4U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:133' */
      /* STOP!! */
      /* '<S3>:1:134' */
      COMMANDER_Y.STATE = 0;
    } else if (COMMANDER_U.BUTTON == 48U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:137' */
      /* '<S3>:1:138' */
      COMMANDER_Y.STATE = 40;
    } else if (COMMANDER_U.BUTTON == 192U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:141' */
      /* '<S3>:1:142' */
      COMMANDER_Y.STATE = 50;
    } else if (COMMANDER_U.BUTTON == 80U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:145' */
      /* '<S3>:1:146' */
      COMMANDER_Y.STATE = 20;
    } else if (COMMANDER_U.CMD_LANDING) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:149' */
      /* '<S3>:1:150' */
      COMMANDER_Y.STATE = 60;
    } else {
      if (COMMANDER_U.CMD_TAKE_OFF) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:153' */
        /* '<S3>:1:154' */
        COMMANDER_Y.STATE = 90;
      }
    }
    break;

   case 40:
    /* Outport: '<Root>/STATE' */
    /* -----------AUTO HIGH LEVEL------------- */
    /* '<S3>:1:159' */
    COMMANDER_Y.STATE = 40;
    if (COMMANDER_U.NO_XBEE) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:160' */
      /* xbee lost */
      /*              if (events(loc_xy_valid) && events(loc_z_valid)) */
      /*                  state_out = LAND; */
      /*                  break; */
      /*              elseif (events(loc_z_valid)) */
      /*                  state_out = Z_LAND; */
      /*                  break; */
      /*              else */
      /*                  state_out = U_LAND; */
      /*                  break; */
      /*              end */
      /* '<S3>:1:171' */
      COMMANDER_Y.STATE = 70;
    } else if (COMMANDER_U.BUTTON == 4U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:174' */
      /* STOP!! */
      /* '<S3>:1:175' */
      COMMANDER_Y.STATE = 0;
    } else if ((!COMMANDER_U.LOC_XY_VALID) && COMMANDER_U.LOC_Z_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:178' */
      /* '<S3>:1:179' */
      COMMANDER_Y.STATE = 80;
    } else if ((!COMMANDER_U.LOC_XY_VALID) && (!COMMANDER_U.LOC_Z_VALID)) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:182' */
      /* '<S3>:1:183' */
      COMMANDER_Y.STATE = 70;
    } else if (COMMANDER_U.BUTTON == 160U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:186' */
      /* '<S3>:1:187' */
      COMMANDER_Y.STATE = 30;
    } else if (COMMANDER_U.BUTTON == 192U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:190' */
      /* '<S3>:1:191' */
      COMMANDER_Y.STATE = 50;
    } else if (COMMANDER_U.BUTTON == 80U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:194' */
      /* '<S3>:1:195' */
      COMMANDER_Y.STATE = 20;
    } else if (COMMANDER_U.CMD_LANDING) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:198' */
      /* '<S3>:1:199' */
      COMMANDER_Y.STATE = 60;
    } else {
      if (COMMANDER_U.CMD_TAKE_OFF) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:202' */
        /* '<S3>:1:203' */
        COMMANDER_Y.STATE = 91;
      }
    }
    break;

   case 50:
    /* Outport: '<Root>/STATE' */
    /* -----------AUTO WAYPOINT------------- */
    /* '<S3>:1:208' */
    COMMANDER_Y.STATE = 50;
    if (COMMANDER_U.NO_XBEE) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:209' */
      /* xbee lost */
      /*              if (events(loc_xy_valid) && events(loc_z_valid)) */
      /*                  state_out = LAND; */
      /*                  break; */
      /*              elseif (events(loc_z_valid)) */
      /*                  state_out = Z_LAND; */
      /*                  break; */
      /*              else */
      /*                  state_out = U_LAND; */
      /*                  break; */
      /*              end */
      /* '<S3>:1:220' */
      COMMANDER_Y.STATE = 70;
    } else if (COMMANDER_U.BUTTON == 4U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:223' */
      /* STOP!! */
      /* '<S3>:1:224' */
      COMMANDER_Y.STATE = 0;
    } else if ((!COMMANDER_U.LOC_XY_VALID) && COMMANDER_U.LOC_Z_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:227' */
      /* '<S3>:1:228' */
      COMMANDER_Y.STATE = 80;
    } else if ((!COMMANDER_U.LOC_XY_VALID) && (!COMMANDER_U.LOC_Z_VALID)) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:231' */
      /* '<S3>:1:232' */
      COMMANDER_Y.STATE = 70;
    } else if (COMMANDER_U.BUTTON == 160U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:235' */
      /* '<S3>:1:236' */
      COMMANDER_Y.STATE = 30;
    } else if (COMMANDER_U.BUTTON == 48U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:239' */
      /* '<S3>:1:240' */
      COMMANDER_Y.STATE = 40;
    } else {
      if (COMMANDER_U.BUTTON == 80U) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:243' */
        /* '<S3>:1:244' */
        COMMANDER_Y.STATE = 20;
      }
    }
    break;

   case 60:
    /* Outport: '<Root>/STATE' */
    /* -----------LANDING------------- */
    /* '<S3>:1:251' */
    COMMANDER_Y.STATE = 60;
    if (COMMANDER_U.BUTTON == 4U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:252' */
      /* STOP!! */
      /* '<S3>:1:253' */
      COMMANDER_Y.STATE = 0;
    } else if ((!COMMANDER_U.LOC_XY_VALID) && COMMANDER_U.LOC_Z_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:256' */
      /* '<S3>:1:257' */
      COMMANDER_Y.STATE = 80;
    } else if ((!COMMANDER_U.LOC_XY_VALID) && (!COMMANDER_U.LOC_Z_VALID)) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:260' */
      /* '<S3>:1:261' */
      COMMANDER_Y.STATE = 70;
    } else {
      if (COMMANDER_U.LANDED) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:264' */
        /* '<S3>:1:265' */
        COMMANDER_Y.STATE = 10;
      }
    }
    break;

   case 70:
    /* Outport: '<Root>/STATE' */
    /* -----------UNCONTROLLED LANDING------------- */
    /* '<S3>:1:270' */
    COMMANDER_Y.STATE = 70;
    if (COMMANDER_U.BUTTON == 4U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:271' */
      /* STOP!! */
      /* '<S3>:1:272' */
      COMMANDER_Y.STATE = 0;
    } else {
      if (COMMANDER_U.LANDED) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:275' */
        /* '<S3>:1:276' */
        COMMANDER_Y.STATE = 10;
      }
    }
    break;

   case 80:
    /* Outport: '<Root>/STATE' */
    /* -----------Z CONTROLLED LANDING------------- */
    /* '<S3>:1:281' */
    COMMANDER_Y.STATE = 80;
    if (COMMANDER_U.BUTTON == 4U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:282' */
      /* STOP!! */
      /* '<S3>:1:283' */
      COMMANDER_Y.STATE = 0;
    } else if (!COMMANDER_U.LOC_Z_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:286' */
      /* '<S3>:1:287' */
      COMMANDER_Y.STATE = 70;
    } else {
      if (COMMANDER_U.LANDED) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:290' */
        /* '<S3>:1:291' */
        COMMANDER_Y.STATE = 10;
      }
    }
    break;

   case 90:
    /* Outport: '<Root>/STATE' */
    /* -----------TAKE OFF FROM LOW LEVEL------------- */
    /* '<S3>:1:296' */
    COMMANDER_Y.STATE = 90;
    if (COMMANDER_U.BUTTON == 4U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:297' */
      /* STOP!! */
      /* '<S3>:1:298' */
      COMMANDER_Y.STATE = 0;
    } else if (COMMANDER_U.NO_XBEE) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:301' */
      /* xbee lost */
      /*              if (events(loc_xy_valid) && events(loc_z_valid)) */
      /*                  state_out = LAND; */
      /*                  break; */
      /*              elseif (events(loc_z_valid)) */
      /*                  state_out = Z_LAND; */
      /*                  break; */
      /*              else */
      /*                  state_out = U_LAND; */
      /*                  break; */
      /*              end */
      /* '<S3>:1:312' */
      COMMANDER_Y.STATE = 70;
    } else if ((!COMMANDER_U.LOC_XY_VALID) && COMMANDER_U.LOC_Z_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:315' */
      /* '<S3>:1:316' */
      COMMANDER_Y.STATE = 80;
    } else if ((!COMMANDER_U.LOC_XY_VALID) && (!COMMANDER_U.LOC_Z_VALID)) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:319' */
      /* '<S3>:1:320' */
      COMMANDER_Y.STATE = 70;
    } else {
      if (COMMANDER_U.TOOK_OFF) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:323' */
        /* '<S3>:1:324' */
        COMMANDER_Y.STATE = 30;
      }
    }
    break;

   case 91:
    /* Outport: '<Root>/STATE' */
    /* -----------TAKE OFF FROM HIGH LEVEL------------- */
    /* '<S3>:1:329' */
    COMMANDER_Y.STATE = 91;
    if (COMMANDER_U.BUTTON == 4U) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:330' */
      /* STOP!! */
      /* '<S3>:1:331' */
      COMMANDER_Y.STATE = 0;
    } else if (COMMANDER_U.NO_XBEE) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:334' */
      /* xbee lost */
      /*              if (events(loc_xy_valid) && events(loc_z_valid)) */
      /*                  state_out = LAND; */
      /*                  break; */
      /*              elseif (events(loc_z_valid)) */
      /*                  state_out = Z_LAND; */
      /*                  break; */
      /*              else */
      /*                  state_out = U_LAND; */
      /*                  break; */
      /*              end */
      /* '<S3>:1:345' */
      COMMANDER_Y.STATE = 70;
    } else if ((!COMMANDER_U.LOC_XY_VALID) && COMMANDER_U.LOC_Z_VALID) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:348' */
      /* '<S3>:1:349' */
      COMMANDER_Y.STATE = 80;
    } else if ((!COMMANDER_U.LOC_XY_VALID) && (!COMMANDER_U.LOC_Z_VALID)) {
      /* Outport: '<Root>/STATE' */
      /* '<S3>:1:352' */
      /* '<S3>:1:353' */
      COMMANDER_Y.STATE = 70;
    } else {
      if (COMMANDER_U.TOOK_OFF) {
        /* Outport: '<Root>/STATE' */
        /* '<S3>:1:356' */
        /* '<S3>:1:357' */
        COMMANDER_Y.STATE = 40;
      }
    }
    break;

   default:
    /* Outport: '<Root>/STATE' */
    /* '<S3>:1:362' */
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
  COMMANDER_M->Sizes.numU = (10);      /* Number of model inputs */
  COMMANDER_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  COMMANDER_M->Sizes.numSampTimes = (1);/* Number of sample times */
  COMMANDER_M->Sizes.numBlocks = (5);  /* Number of blocks */
  COMMANDER_M->Sizes.numBlockIO = (1); /* Number of block outputs */
  return COMMANDER_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
