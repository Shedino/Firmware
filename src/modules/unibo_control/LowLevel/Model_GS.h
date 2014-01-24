/*
 * Model_GS.h
 *
 * Code generation for model "Model_GS".
 *
 * Model version              : 1.2333
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Tue Jan 21 16:23:36 2014
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#ifndef RTW_HEADER_Model_GS_h_
#define RTW_HEADER_Model_GS_h_
#ifndef Model_GS_COMMON_INCLUDES_
# define Model_GS_COMMON_INCLUDES_
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#endif                                 /* Model_GS_COMMON_INCLUDES_ */

#include "Model_GS_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlkStateChangeFlag
# define rtmGetBlkStateChangeFlag(rtm) ((rtm)->ModelData.blkStateChange)
#endif

#ifndef rtmSetBlkStateChangeFlag
# define rtmSetBlkStateChangeFlag(rtm, val) ((rtm)->ModelData.blkStateChange = (val))
#endif

#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->ModelData.blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->ModelData.blockIO = (val))
#endif

#ifndef rtmGetChecksums
# define rtmGetChecksums(rtm)          ((rtm)->Sizes.checksums)
#endif

#ifndef rtmSetChecksums
# define rtmSetChecksums(rtm, val)     ((rtm)->Sizes.checksums = (val))
#endif

#ifndef rtmGetConstBlockIO
# define rtmGetConstBlockIO(rtm)       ((rtm)->ModelData.constBlockIO)
#endif

#ifndef rtmSetConstBlockIO
# define rtmSetConstBlockIO(rtm, val)  ((rtm)->ModelData.constBlockIO = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->ModelData.contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->ModelData.contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->ModelData.contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->ModelData.contStates = (val))
#endif

#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ()
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ()
#endif

#ifndef rtmGetDefaultParam
# define rtmGetDefaultParam(rtm)       ((rtm)->ModelData.defaultParam)
#endif

#ifndef rtmSetDefaultParam
# define rtmSetDefaultParam(rtm, val)  ((rtm)->ModelData.defaultParam = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->ModelData.derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->ModelData.derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetDirectFeedThrough
# define rtmGetDirectFeedThrough(rtm)  ((rtm)->Sizes.sysDirFeedThru)
#endif

#ifndef rtmSetDirectFeedThrough
# define rtmSetDirectFeedThrough(rtm, val) ((rtm)->Sizes.sysDirFeedThru = (val))
#endif

#ifndef rtmGetErrorStatusFlag
# define rtmGetErrorStatusFlag(rtm)    ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatusFlag
# define rtmSetErrorStatusFlag(rtm, val) ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetFinalTime
# define rtmSetFinalTime(rtm, val)     ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetFirstInitCondFlag
# define rtmGetFirstInitCondFlag(rtm)  ()
#endif

#ifndef rtmSetFirstInitCondFlag
# define rtmSetFirstInitCondFlag(rtm, val) ()
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ()
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ()
#endif

#ifndef rtmGetMdlRefGlobalTID
# define rtmGetMdlRefGlobalTID(rtm)    ()
#endif

#ifndef rtmSetMdlRefGlobalTID
# define rtmSetMdlRefGlobalTID(rtm, val) ()
#endif

#ifndef rtmGetMdlRefTriggerTID
# define rtmGetMdlRefTriggerTID(rtm)   ()
#endif

#ifndef rtmSetMdlRefTriggerTID
# define rtmSetMdlRefTriggerTID(rtm, val) ()
#endif

#ifndef rtmGetModelMappingInfo
# define rtmGetModelMappingInfo(rtm)   ((rtm)->SpecialInfo.mappingInfo)
#endif

#ifndef rtmSetModelMappingInfo
# define rtmSetModelMappingInfo(rtm, val) ((rtm)->SpecialInfo.mappingInfo = (val))
#endif

#ifndef rtmGetModelName
# define rtmGetModelName(rtm)          ((rtm)->modelName)
#endif

#ifndef rtmSetModelName
# define rtmSetModelName(rtm, val)     ((rtm)->modelName = (val))
#endif

#ifndef rtmGetNonInlinedSFcns
# define rtmGetNonInlinedSFcns(rtm)    ()
#endif

#ifndef rtmSetNonInlinedSFcns
# define rtmSetNonInlinedSFcns(rtm, val) ()
#endif

#ifndef rtmGetNumBlockIO
# define rtmGetNumBlockIO(rtm)         ((rtm)->Sizes.numBlockIO)
#endif

#ifndef rtmSetNumBlockIO
# define rtmSetNumBlockIO(rtm, val)    ((rtm)->Sizes.numBlockIO = (val))
#endif

#ifndef rtmGetNumBlockParams
# define rtmGetNumBlockParams(rtm)     ((rtm)->Sizes.numBlockPrms)
#endif

#ifndef rtmSetNumBlockParams
# define rtmSetNumBlockParams(rtm, val) ((rtm)->Sizes.numBlockPrms = (val))
#endif

#ifndef rtmGetNumBlocks
# define rtmGetNumBlocks(rtm)          ((rtm)->Sizes.numBlocks)
#endif

#ifndef rtmSetNumBlocks
# define rtmSetNumBlocks(rtm, val)     ((rtm)->Sizes.numBlocks = (val))
#endif

#ifndef rtmGetNumContStates
# define rtmGetNumContStates(rtm)      ((rtm)->Sizes.numContStates)
#endif

#ifndef rtmSetNumContStates
# define rtmSetNumContStates(rtm, val) ((rtm)->Sizes.numContStates = (val))
#endif

#ifndef rtmGetNumDWork
# define rtmGetNumDWork(rtm)           ((rtm)->Sizes.numDwork)
#endif

#ifndef rtmSetNumDWork
# define rtmSetNumDWork(rtm, val)      ((rtm)->Sizes.numDwork = (val))
#endif

#ifndef rtmGetNumInputPorts
# define rtmGetNumInputPorts(rtm)      ((rtm)->Sizes.numIports)
#endif

#ifndef rtmSetNumInputPorts
# define rtmSetNumInputPorts(rtm, val) ((rtm)->Sizes.numIports = (val))
#endif

#ifndef rtmGetNumNonSampledZCs
# define rtmGetNumNonSampledZCs(rtm)   ((rtm)->Sizes.numNonSampZCs)
#endif

#ifndef rtmSetNumNonSampledZCs
# define rtmSetNumNonSampledZCs(rtm, val) ((rtm)->Sizes.numNonSampZCs = (val))
#endif

#ifndef rtmGetNumOutputPorts
# define rtmGetNumOutputPorts(rtm)     ((rtm)->Sizes.numOports)
#endif

#ifndef rtmSetNumOutputPorts
# define rtmSetNumOutputPorts(rtm, val) ((rtm)->Sizes.numOports = (val))
#endif

#ifndef rtmGetNumSFcnParams
# define rtmGetNumSFcnParams(rtm)      ((rtm)->Sizes.numSFcnPrms)
#endif

#ifndef rtmSetNumSFcnParams
# define rtmSetNumSFcnParams(rtm, val) ((rtm)->Sizes.numSFcnPrms = (val))
#endif

#ifndef rtmGetNumSFunctions
# define rtmGetNumSFunctions(rtm)      ((rtm)->Sizes.numSFcns)
#endif

#ifndef rtmSetNumSFunctions
# define rtmSetNumSFunctions(rtm, val) ((rtm)->Sizes.numSFcns = (val))
#endif

#ifndef rtmGetNumSampleTimes
# define rtmGetNumSampleTimes(rtm)     ((rtm)->Sizes.numSampTimes)
#endif

#ifndef rtmSetNumSampleTimes
# define rtmSetNumSampleTimes(rtm, val) ((rtm)->Sizes.numSampTimes = (val))
#endif

#ifndef rtmGetNumU
# define rtmGetNumU(rtm)               ((rtm)->Sizes.numU)
#endif

#ifndef rtmSetNumU
# define rtmSetNumU(rtm, val)          ((rtm)->Sizes.numU = (val))
#endif

#ifndef rtmGetNumY
# define rtmGetNumY(rtm)               ((rtm)->Sizes.numY)
#endif

#ifndef rtmSetNumY
# define rtmSetNumY(rtm, val)          ((rtm)->Sizes.numY = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ()
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ()
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ()
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ()
#endif

#ifndef rtmGetOffsetTimeArray
# define rtmGetOffsetTimeArray(rtm)    ((rtm)->Timing.offsetTimesArray)
#endif

#ifndef rtmSetOffsetTimeArray
# define rtmSetOffsetTimeArray(rtm, val) ((rtm)->Timing.offsetTimesArray = (val))
#endif

#ifndef rtmGetOffsetTimePtr
# define rtmGetOffsetTimePtr(rtm)      ((rtm)->Timing.offsetTimes)
#endif

#ifndef rtmSetOffsetTimePtr
# define rtmSetOffsetTimePtr(rtm, val) ((rtm)->Timing.offsetTimes = (val))
#endif

#ifndef rtmGetOptions
# define rtmGetOptions(rtm)            ((rtm)->Sizes.options)
#endif

#ifndef rtmSetOptions
# define rtmSetOptions(rtm, val)       ((rtm)->Sizes.options = (val))
#endif

#ifndef rtmGetParamIsMalloced
# define rtmGetParamIsMalloced(rtm)    ()
#endif

#ifndef rtmSetParamIsMalloced
# define rtmSetParamIsMalloced(rtm, val) ()
#endif

#ifndef rtmGetPath
# define rtmGetPath(rtm)               ((rtm)->path)
#endif

#ifndef rtmSetPath
# define rtmSetPath(rtm, val)          ((rtm)->path = (val))
#endif

#ifndef rtmGetPerTaskSampleHits
# define rtmGetPerTaskSampleHits(rtm)  ()
#endif

#ifndef rtmSetPerTaskSampleHits
# define rtmSetPerTaskSampleHits(rtm, val) ()
#endif

#ifndef rtmGetPerTaskSampleHitsArray
# define rtmGetPerTaskSampleHitsArray(rtm) ((rtm)->Timing.perTaskSampleHitsArray)
#endif

#ifndef rtmSetPerTaskSampleHitsArray
# define rtmSetPerTaskSampleHitsArray(rtm, val) ((rtm)->Timing.perTaskSampleHitsArray = (val))
#endif

#ifndef rtmGetPerTaskSampleHitsPtr
# define rtmGetPerTaskSampleHitsPtr(rtm) ((rtm)->Timing.perTaskSampleHits)
#endif

#ifndef rtmSetPerTaskSampleHitsPtr
# define rtmSetPerTaskSampleHitsPtr(rtm, val) ((rtm)->Timing.perTaskSampleHits = (val))
#endif

#ifndef rtmGetPrevZCSigState
# define rtmGetPrevZCSigState(rtm)     ((rtm)->ModelData.prevZCSigState)
#endif

#ifndef rtmSetPrevZCSigState
# define rtmSetPrevZCSigState(rtm, val) ((rtm)->ModelData.prevZCSigState = (val))
#endif

#ifndef rtmGetRTWExtModeInfo
# define rtmGetRTWExtModeInfo(rtm)     ((rtm)->extModeInfo)
#endif

#ifndef rtmSetRTWExtModeInfo
# define rtmSetRTWExtModeInfo(rtm, val) ((rtm)->extModeInfo = (val))
#endif

#ifndef rtmGetRTWGeneratedSFcn
# define rtmGetRTWGeneratedSFcn(rtm)   ((rtm)->Sizes.rtwGenSfcn)
#endif

#ifndef rtmSetRTWGeneratedSFcn
# define rtmSetRTWGeneratedSFcn(rtm, val) ((rtm)->Sizes.rtwGenSfcn = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ()
#endif

#ifndef rtmSetRTWLogInfo
# define rtmSetRTWLogInfo(rtm, val)    ()
#endif

#ifndef rtmGetRTWRTModelMethodsInfo
# define rtmGetRTWRTModelMethodsInfo(rtm) ()
#endif

#ifndef rtmSetRTWRTModelMethodsInfo
# define rtmSetRTWRTModelMethodsInfo(rtm, val) ()
#endif

#ifndef rtmGetRTWSfcnInfo
# define rtmGetRTWSfcnInfo(rtm)        ((rtm)->sfcnInfo)
#endif

#ifndef rtmSetRTWSfcnInfo
# define rtmSetRTWSfcnInfo(rtm, val)   ((rtm)->sfcnInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfo
# define rtmGetRTWSolverInfo(rtm)      ((rtm)->solverInfo)
#endif

#ifndef rtmSetRTWSolverInfo
# define rtmSetRTWSolverInfo(rtm, val) ((rtm)->solverInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfoPtr
# define rtmGetRTWSolverInfoPtr(rtm)   ((rtm)->solverInfoPtr)
#endif

#ifndef rtmSetRTWSolverInfoPtr
# define rtmSetRTWSolverInfoPtr(rtm, val) ((rtm)->solverInfoPtr = (val))
#endif

#ifndef rtmGetReservedForXPC
# define rtmGetReservedForXPC(rtm)     ((rtm)->SpecialInfo.xpcData)
#endif

#ifndef rtmSetReservedForXPC
# define rtmSetReservedForXPC(rtm, val) ((rtm)->SpecialInfo.xpcData = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->Work.dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->Work.dwork = (val))
#endif

#ifndef rtmGetSFunctions
# define rtmGetSFunctions(rtm)         ((rtm)->childSfunctions)
#endif

#ifndef rtmSetSFunctions
# define rtmSetSFunctions(rtm, val)    ((rtm)->childSfunctions = (val))
#endif

#ifndef rtmGetSampleHitArray
# define rtmGetSampleHitArray(rtm)     ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmSetSampleHitArray
# define rtmSetSampleHitArray(rtm, val) ((rtm)->Timing.sampleHitArray = (val))
#endif

#ifndef rtmGetSampleHitPtr
# define rtmGetSampleHitPtr(rtm)       ((rtm)->Timing.sampleHits)
#endif

#ifndef rtmSetSampleHitPtr
# define rtmSetSampleHitPtr(rtm, val)  ((rtm)->Timing.sampleHits = (val))
#endif

#ifndef rtmGetSampleTimeArray
# define rtmGetSampleTimeArray(rtm)    ((rtm)->Timing.sampleTimesArray)
#endif

#ifndef rtmSetSampleTimeArray
# define rtmSetSampleTimeArray(rtm, val) ((rtm)->Timing.sampleTimesArray = (val))
#endif

#ifndef rtmGetSampleTimePtr
# define rtmGetSampleTimePtr(rtm)      ((rtm)->Timing.sampleTimes)
#endif

#ifndef rtmSetSampleTimePtr
# define rtmSetSampleTimePtr(rtm, val) ((rtm)->Timing.sampleTimes = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDArray
# define rtmGetSampleTimeTaskIDArray(rtm) ((rtm)->Timing.sampleTimeTaskIDArray)
#endif

#ifndef rtmSetSampleTimeTaskIDArray
# define rtmSetSampleTimeTaskIDArray(rtm, val) ((rtm)->Timing.sampleTimeTaskIDArray = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDPtr
# define rtmGetSampleTimeTaskIDPtr(rtm) ((rtm)->Timing.sampleTimeTaskIDPtr)
#endif

#ifndef rtmSetSampleTimeTaskIDPtr
# define rtmSetSampleTimeTaskIDPtr(rtm, val) ((rtm)->Timing.sampleTimeTaskIDPtr = (val))
#endif

#ifndef rtmGetSimMode
# define rtmGetSimMode(rtm)            ((rtm)->simMode)
#endif

#ifndef rtmSetSimMode
# define rtmSetSimMode(rtm, val)       ((rtm)->simMode = (val))
#endif

#ifndef rtmGetSimTimeStep
# define rtmGetSimTimeStep(rtm)        ((rtm)->Timing.simTimeStep)
#endif

#ifndef rtmSetSimTimeStep
# define rtmSetSimTimeStep(rtm, val)   ((rtm)->Timing.simTimeStep = (val))
#endif

#ifndef rtmGetStartTime
# define rtmGetStartTime(rtm)          ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetStartTime
# define rtmSetStartTime(rtm, val)     ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetStepSize
# define rtmGetStepSize(rtm)           ((rtm)->Timing.stepSize)
#endif

#ifndef rtmSetStepSize
# define rtmSetStepSize(rtm, val)      ((rtm)->Timing.stepSize = (val))
#endif

#ifndef rtmGetStopRequestedFlag
# define rtmGetStopRequestedFlag(rtm)  ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequestedFlag
# define rtmSetStopRequestedFlag(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetTaskCounters
# define rtmGetTaskCounters(rtm)       ()
#endif

#ifndef rtmSetTaskCounters
# define rtmSetTaskCounters(rtm, val)  ()
#endif

#ifndef rtmGetTaskTimeArray
# define rtmGetTaskTimeArray(rtm)      ((rtm)->Timing.tArray)
#endif

#ifndef rtmSetTaskTimeArray
# define rtmSetTaskTimeArray(rtm, val) ((rtm)->Timing.tArray = (val))
#endif

#ifndef rtmGetTimePtr
# define rtmGetTimePtr(rtm)            ((rtm)->Timing.t)
#endif

#ifndef rtmSetTimePtr
# define rtmSetTimePtr(rtm, val)       ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTimingData
# define rtmGetTimingData(rtm)         ((rtm)->Timing.timingData)
#endif

#ifndef rtmSetTimingData
# define rtmSetTimingData(rtm, val)    ((rtm)->Timing.timingData = (val))
#endif

#ifndef rtmGetU
# define rtmGetU(rtm)                  ((rtm)->ModelData.inputs)
#endif

#ifndef rtmSetU
# define rtmSetU(rtm, val)             ((rtm)->ModelData.inputs = (val))
#endif

#ifndef rtmGetVarNextHitTimesListPtr
# define rtmGetVarNextHitTimesListPtr(rtm) ((rtm)->Timing.varNextHitTimesList)
#endif

#ifndef rtmSetVarNextHitTimesListPtr
# define rtmSetVarNextHitTimesListPtr(rtm, val) ((rtm)->Timing.varNextHitTimesList = (val))
#endif

#ifndef rtmGetY
# define rtmGetY(rtm)                  ((rtm)->ModelData.outputs)
#endif

#ifndef rtmSetY
# define rtmSetY(rtm, val)             ((rtm)->ModelData.outputs = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->ModelData.zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->ModelData.zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetZCSignalValues
# define rtmGetZCSignalValues(rtm)     ((rtm)->ModelData.zcSignalValues)
#endif

#ifndef rtmSetZCSignalValues
# define rtmSetZCSignalValues(rtm, val) ((rtm)->ModelData.zcSignalValues = (val))
#endif

#ifndef rtmGet_TimeOfLastOutput
# define rtmGet_TimeOfLastOutput(rtm)  ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmSet_TimeOfLastOutput
# define rtmSet_TimeOfLastOutput(rtm, val) ((rtm)->Timing.timeOfLastOutput = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->ModelData.derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->ModelData.derivs = (val))
#endif

#ifndef rtmGetChecksumVal
# define rtmGetChecksumVal(rtm, idx)   ((rtm)->Sizes.checksums[idx])
#endif

#ifndef rtmSetChecksumVal
# define rtmSetChecksumVal(rtm, idx, val) ((rtm)->Sizes.checksums[idx] = (val))
#endif

#ifndef rtmGetDWork
# define rtmGetDWork(rtm, idx)         ((rtm)->Work.dwork[idx])
#endif

#ifndef rtmSetDWork
# define rtmSetDWork(rtm, idx, val)    ((rtm)->Work.dwork[idx] = (val))
#endif

#ifndef rtmGetOffsetTime
# define rtmGetOffsetTime(rtm, idx)    ((rtm)->Timing.offsetTimes[idx])
#endif

#ifndef rtmSetOffsetTime
# define rtmSetOffsetTime(rtm, idx, val) ((rtm)->Timing.offsetTimes[idx] = (val))
#endif

#ifndef rtmGetSFunction
# define rtmGetSFunction(rtm, idx)     ((rtm)->childSfunctions[idx])
#endif

#ifndef rtmSetSFunction
# define rtmSetSFunction(rtm, idx, val) ((rtm)->childSfunctions[idx] = (val))
#endif

#ifndef rtmGetSampleTime
# define rtmGetSampleTime(rtm, idx)    ((rtm)->Timing.sampleTimes[idx])
#endif

#ifndef rtmSetSampleTime
# define rtmSetSampleTime(rtm, idx, val) ((rtm)->Timing.sampleTimes[idx] = (val))
#endif

#ifndef rtmGetSampleTimeTaskID
# define rtmGetSampleTimeTaskID(rtm, idx) ((rtm)->Timing.sampleTimeTaskIDPtr[idx])
#endif

#ifndef rtmSetSampleTimeTaskID
# define rtmSetSampleTimeTaskID(rtm, idx, val) ((rtm)->Timing.sampleTimeTaskIDPtr[idx] = (val))
#endif

#ifndef rtmGetVarNextHitTimeList
# define rtmGetVarNextHitTimeList(rtm, idx) ((rtm)->Timing.varNextHitTimesList[idx])
#endif

#ifndef rtmSetVarNextHitTimeList
# define rtmSetVarNextHitTimeList(rtm, idx, val) ((rtm)->Timing.varNextHitTimesList[idx] = (val))
#endif

#ifndef rtmIsContinuousTask
# define rtmIsContinuousTask(rtm, tid) 0
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmIsSampleHit
# define rtmIsSampleHit(rtm, sti, tid) ((rtm)->Timing.sampleHits[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmSetT
# define rtmSetT(rtm, val)                                       /* Do Nothing */
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTStart
# define rtmGetTStart(rtm)             ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetTStart
# define rtmSetTStart(rtm, val)        ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetTaskTime
# define rtmGetTaskTime(rtm, sti)      (rtmGetTPtr((rtm))[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
#endif

#ifndef rtmSetTaskTime
# define rtmSetTaskTime(rtm, sti, val) (rtmGetTPtr((rtm))[sti] = (val))
#endif

#ifndef rtmGetTimeOfLastOutput
# define rtmGetTimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

#ifdef rtmGetRTWSolverInfo
#undef rtmGetRTWSolverInfo
#endif

#define rtmGetRTWSolverInfo(rtm)       &((rtm)->solverInfo)

/* Definition for use in the target main file */
#define Model_GS_rtModel               RT_MODEL_Model_GS

/* Block signals for system '<S50>/Euler's backward metohd' */
typedef struct {
  real_T a;                            /* '<S50>/Euler's backward metohd' */
} rtB_Eulersbackwardmetohd_Model_;

/* Block signals (auto storage) */
typedef struct {
  real_T Sum3;                         /* '<S58>/Sum3' */
  real_T Sum[3];                       /* '<S47>/Sum' */
  real_T EN;                           /* '<S38>/Enable' */
  real_T u0[3];                        /* '<S38>/Enable' */
  real_T nextState;                    /* '<S29>/STATE TRANSITIONS' */
  real_T nextResetState;               /* '<S29>/STATE TRANSITIONS' */
  real_T countNew;                     /* '<S25>/RESET CIRCUIT' */
  real_T h1;                           /* '<S12>/Attitude controller' */
  real32_T DataTypeConversion1[2];     /* '<Root>/Data Type Conversion1' */
  real32_T Sum_f[3];                   /* '<S8>/Sum' */
  real32_T p[3];                       /* '<S32>/parser' */
  real32_T q[4];                       /* '<S32>/parser' */
  real32_T Tstamp;                     /* '<S32>/parser' */
  real32_T normaP;                     /* '<S32>/parser' */
  real32_T dx1hat[3];                  /* '<S67>/High-Gain Observer' */
  real32_T dx2hat[3];                  /* '<S67>/High-Gain Observer' */
  real32_T dp[3];                      /* '<S32>/VELOCITY' */
  real32_T MAG_comp[3];                /* '<S62>/MAG Compensation' */
  real32_T Sum_m[3];                   /* '<S50>/Sum' */
  real32_T Sum_g[3];                   /* '<S51>/Sum' */
  real32_T xk_pri[10];                 /* '<S37>/Mechanization' */
  real32_T w[3];                       /* '<S37>/Mechanization' */
  real32_T xk_post[10];                /* '<S39>/State Update' */
  real32_T Pkp1_pri[81];               /* '<S39>/Kalman Gain' */
  uint16_T CINPUTS[11];                /* '<S7>/cinputs' */
  boolean_T DataTypeConversion3;       /* '<S25>/Data Type Conversion3' */
  rtB_Eulersbackwardmetohd_Model_ sf_Eulersbackwardmetohd_h;/* '<S47>/Euler's backward metohd' */
  rtB_Eulersbackwardmetohd_Model_ sf_Eulersbackwardmetohd_n;/* '<S51>/Euler's backward metohd' */
  rtB_Eulersbackwardmetohd_Model_ sf_Eulersbackwardmetohd;/* '<S50>/Euler's backward metohd' */
} BlockIO_Model_GS;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Memory1_PreviousInput;        /* '<S29>/Memory1' */
  real_T Memory3_PreviousInput;        /* '<S29>/Memory3' */
  real_T Memory_PreviousInput;         /* '<S25>/Memory' */
  real_T Memory_PreviousInput_b;       /* '<S58>/Memory' */
  real_T Memory2_PreviousInput[4];     /* '<S16>/Memory2' */
  real_T Memory_PreviousInput_g;       /* '<S12>/Memory' */
  real_T ytk1_PreviousInput[3];        /* '<S47>/y(tk-1)' */
  real_T Memory_PreviousInput_m[3];    /* '<S38>/Memory' */
  real32_T BesselLPFdX_states[2];      /* '<S65>/Bessel LPF dX' */
  real32_T BesselLPFdY_states[2];      /* '<S65>/Bessel LPF dY' */
  real32_T BesselLPFdZ_states[2];      /* '<S65>/Bessel LPF dZ' */
  real32_T DiscreteTimeIntegrator1_DSTATE[3];/* '<S8>/Discrete-Time Integrator1' */
  real32_T x1hat_DSTATE[3];            /* '<S67>/x1hat' */
  real32_T x2hat_DSTATE[3];            /* '<S67>/x2hat' */
  real32_T FixPtUnitDelay1_DSTATE[10]; /* '<S41>/FixPt Unit Delay1' */
  real32_T UnitDelay_DSTATE[81];       /* '<S39>/Unit Delay' */
  real32_T Memory6_PreviousInput[3];   /* '<S32>/Memory6' */
  real32_T Memory5_PreviousInput[4];   /* '<S32>/Memory5' */
  real32_T Memory4_PreviousInput;      /* '<S32>/Memory4' */
  real32_T Memory3_PreviousInput_e;    /* '<S32>/Memory3' */
  real32_T Memory_PreviousInput_o[3];  /* '<S62>/Memory' */
  real32_T Memory_PreviousInput_op[3]; /* '<S32>/Memory' */
  real32_T Memory1_PreviousInput_g;    /* '<S32>/Memory1' */
  real32_T Memory2_PreviousInput_k[3]; /* '<S32>/Memory2' */
  real32_T ytk1_PreviousInput_o[3];    /* '<S50>/y(tk-1)' */
  real32_T ytk1_PreviousInput_f[3];    /* '<S51>/y(tk-1)' */
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S41>/FixPt Unit Delay2' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S8>/Discrete-Time Integrator1' */
} D_Work_Model_GS;

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: J
   * Referenced by: '<S12>/Attitude controller'
   */
  real_T SFunction_p1[9];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S39>/Constant4'
   *   '<S39>/Constant5'
   */
  real_T pooled3[9];

  /* Expression: R
   * Referenced by: '<S39>/Constant6'
   */
  real_T Constant6_Value[36];

  /* Expression: Q
   * Referenced by: '<S39>/Constant7'
   */
  real_T Constant7_Value[81];

  /* Expression: ACC_gain
   * Referenced by: '<S62>/Constant'
   */
  real_T Constant_Value[9];

  /* Expression: ACC_offset
   * Referenced by: '<S62>/Constant1'
   */
  real_T Constant1_Value[3];

  /* Computed Parameter: UnitDelay_InitialCon
   * Referenced by: '<S39>/Unit Delay'
   */
  real32_T UnitDelay_InitialCon[81];
} ConstParam_Model_GS;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  int16_T IMUPacket[14];               /* '<Root>/IMUPacket' */
  int16_T IMUCounter[2];               /* '<Root>/IMUCounter' */
  int16_T OFLOW[4];                    /* '<Root>/OFLOW' */
  int16_T LLS[3];                      /* '<Root>/LLS' */
  int16_T LLSenable;                   /* '<Root>/LLSenable' */
  int16_T REF_TIME[18];                /* '<Root>/REF_TIME' */
  int32_T PARAMETERS[28];              /* '<Root>/PARAMETERS' */
  int16_T TIME_ATOM;                   /* '<Root>/TIME_ATOM' */
  int16_T OPTITRACK[12];               /* '<Root>/OPTITRACK' */
} ExternalInputs_Model_GS;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  uint16_T CINPUTS[11];                /* '<Root>/CINPUTS' */
  int16_T STATE[12];                   /* '<Root>/STATE' */
  real32_T C_TORQUES[3];               /* '<Root>/C_TORQUES' */
  real32_T C_Q[4];                     /* '<Root>/C_Q' */
  real_T C_QC[4];                      /* '<Root>/C_QC' */
  real32_T C_THRUST;                   /* '<Root>/C_THRUST' */
} ExternalOutputs_Model_GS;

/* Backward compatible GRT Identifiers */
#define rtB                            Model_GS_B
#define BlockIO                        BlockIO_Model_GS
#define rtU                            Model_GS_U
#define ExternalInputs                 ExternalInputs_Model_GS
#define rtY                            Model_GS_Y
#define ExternalOutputs                ExternalOutputs_Model_GS
#define rtDWork                        Model_GS_DWork
#define D_Work                         D_Work_Model_GS
#define ConstParam                     ConstParam_Model_GS
#define rtcP                           Model_GS_ConstP

/* Real-time Model Data Structure */
struct tag_RTM_Model_GS {
  const char_T *path;
  const char_T *modelName;
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    void *blockIO;
    const void *constBlockIO;
    void *defaultParam;
    ZCSigState *prevZCSigState;
    real_T *contStates;
    real_T *derivs;
    void *zcSignalValues;
    void *inputs;
    void *outputs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
  } ModelData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
    uint32_T options;
    int_T numContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
    void *xpcData;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    void *timingData;
    real_T *varNextHitTimesList;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[1];
    time_T offsetTimesArray[1];
    int_T sampleTimeTaskIDArray[1];
    int_T sampleHitArray[1];
    int_T perTaskSampleHitsArray[1];
    time_T tArray[1];
  } Timing;

  /*
   * Work:
   * The following substructure contains information regarding
   * the work vectors in the model.
   */
  struct {
    void *dwork;
  } Work;
};

/* Block signals (auto storage) */
extern BlockIO_Model_GS Model_GS_B;

/* Block states (auto storage) */
extern D_Work_Model_GS Model_GS_DWork;

/* External inputs (root inport signals with auto storage) */
extern ExternalInputs_Model_GS Model_GS_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExternalOutputs_Model_GS Model_GS_Y;

/* Constant parameters (auto storage) */
extern const ConstParam_Model_GS Model_GS_ConstP;

/* Real-time Model object */
extern RT_MODEL_Model_GS *const Model_GS_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Model_GS'
 * '<S1>'   : 'Model_GS/LOW-LEVEL CONTROL'
 * '<S2>'   : 'Model_GS/LOW-LEVEL CONTROL/CONTROL'
 * '<S3>'   : 'Model_GS/LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR'
 * '<S4>'   : 'Model_GS/LOW-LEVEL CONTROL/PARAM'
 * '<S5>'   : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES'
 * '<S6>'   : 'Model_GS/LOW-LEVEL CONTROL/UAV_STATE'
 * '<S7>'   : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/MOTOR ALLOCATION & GE  COMPENSATION'
 * '<S8>'   : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW'
 * '<S9>'   : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/R&p_fromstate'
 * '<S10>'  : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/MOTOR ALLOCATION & GE  COMPENSATION/ALLOCATION'
 * '<S11>'  : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/MOTOR ALLOCATION & GE  COMPENSATION/cinputs'
 * '<S12>'  : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK'
 * '<S13>'  : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/setpoint_conversion1'
 * '<S14>'  : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Abs(v*)'
 * '<S15>'  : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Attitude controller'
 * '<S16>'  : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/DCM to consistent Quaternion '
 * '<S17>'  : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Position controller'
 * '<S18>'  : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/R* from v* and psi*1'
 * '<S19>'  : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Reference generation'
 * '<S20>'  : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/DCM to consistent Quaternion /DCM to quaternion '
 * '<S21>'  : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/DCM to consistent Quaternion /Quaternion choice1'
 * '<S22>'  : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Reference generation/R* from v* and psi+'
 * '<S23>'  : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Reference generation/R* from v* and psi*1'
 * '<S24>'  : 'Model_GS/LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Reference generation/v* from p*, p'* and p''+'
 * '<S25>'  : 'Model_GS/LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR'
 * '<S26>'  : 'Model_GS/LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/Embedded MATLAB Function'
 * '<S27>'  : 'Model_GS/LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/MOTOR CONTROL'
 * '<S28>'  : 'Model_GS/LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/RESET CIRCUIT'
 * '<S29>'  : 'Model_GS/LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/STATE MACHINE'
 * '<S30>'  : 'Model_GS/LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/STATE MACHINE/STATE TRANSITIONS'
 * '<S31>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1'
 * '<S32>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK'
 * '<S33>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/REFERENCES'
 * '<S34>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS'
 * '<S35>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4'
 * '<S36>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/z rotation'
 * '<S37>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/FILTER'
 * '<S38>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization'
 * '<S39>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/FILTER/EKF'
 * '<S40>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/FILTER/Mechanization'
 * '<S41>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/FILTER/Unit Delay External IC'
 * '<S42>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/FILTER/EKF/Kalman Gain'
 * '<S43>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/FILTER/EKF/Residuals'
 * '<S44>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/FILTER/EKF/State Update'
 * '<S45>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Enable'
 * '<S46>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Euler Angles'
 * '<S47>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/LPF u'
 * '<S48>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Quaternion'
 * '<S49>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Euler Angles/Gyro Compassing'
 * '<S50>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Euler Angles/LPF ya'
 * '<S51>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Euler Angles/LPF ym'
 * '<S52>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Euler Angles/Gyro Compassing/mw (10.16)'
 * '<S53>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Euler Angles/LPF ya/Euler's backward metohd'
 * '<S54>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Euler Angles/LPF ym/Euler's backward metohd'
 * '<S55>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/LPF u/Euler's backward metohd'
 * '<S56>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Quaternion/Quaternion'
 * '<S57>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Quaternion/Rnb (NED TO BODY)'
 * '<S58>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/COUNTER'
 * '<S59>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/Mounting'
 * '<S60>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/Parser'
 * '<S61>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/Parser_deltaT'
 * '<S62>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/RAW Compensation'
 * '<S63>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/RAW Compensation/ACC Compensation'
 * '<S64>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/RAW Compensation/MAG Compensation'
 * '<S65>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/BESSEL FILTER'
 * '<S66>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/VELOCITY'
 * '<S67>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/dP Observer'
 * '<S68>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/parser'
 * '<S69>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/dP Observer/BESSEL FILTER'
 * '<S70>'  : 'Model_GS/LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/dP Observer/High-Gain Observer'
 */
#endif                                 /* RTW_HEADER_Model_GS_h_ */