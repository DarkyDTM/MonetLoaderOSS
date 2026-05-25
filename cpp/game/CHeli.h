#pragma once
#include "CAutomobile.h"

struct CHeli : public CAutomobile {
  union {
    unsigned char nHeliFlags;
    struct
    {
      unsigned char bStopFlyingForAWhile : 1;
      unsigned char bUseSearchLightOnTarget : 1;
      unsigned char bWarnTarger : 1;
    } heliFlags;
  };
  float fLeftRightSkid; // m_fYawControl
  float fSteeringUpDown; // m_fPitchControl
  float fSteeringLeftRight; // m_fRollControl
  float fAccelerationBreakStatus; // m_fThrottleControl
  float field_99C; // m_fEngineSpeed
  float fRotorZ;
  float fSecondRotorZ;
  float fMaxAltitude;
  float field_9AC; // m_fDesiredHeight
  float fMinAltitude;
  float field_9B4; // m_FlightDirection
  char field_9B8; // m_bStopFlyingForAWhile
  unsigned char nNumSwatOccupants;
  unsigned char anSwatIDs[4]; // m_SwatRopeActive
  float afOldSearchLightX[6];
  float afOldSearchLightY[6];
  unsigned int field_9F0; // m_LastSearchLightSample
  CVector vSearchLightTarget;
  float fSearchLightIntensity;
  unsigned int field_A04; // m_LastTimeSearchLightWasTooFarAwayToShoot
  unsigned int field_A08; // m_nNextTalkTimer
  void** ppGunflashFx;
  unsigned char nFiringMultiplier;
  char bSearchLightEnabled;
  float field_A14; // m_crashAndBurnTurnSpeed
};