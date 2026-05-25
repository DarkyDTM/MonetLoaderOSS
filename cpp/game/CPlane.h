#include "CAutomobile.h"

struct CPlane : CAutomobile {
  float m_fYawControl;
  float m_fPitchControl;
  float m_fRollControl;
  float m_fThrottleControl;
  float m_fScriptThrottleControl;
  float m_fPreviousRoll;
  std::uint32_t m_nStallCounter;
  float m_TakeOffDirection;
  float m_LowestFlightHeight;
  float m_DesiredHeight;
  float m_MinHeightAboveTerrain;
  float m_FlightDirection;
  float m_FlightDirectionAvoidingTerrain;
  float m_OldTilt;
  std::uint32_t m_OnGroundTimer;
  float m_fEngineSpeed;
  float m_fPropellerAngle;
  float m_fLGearAngle;
  std::uint32_t m_nDamageControlWaveCounter;
  void** m_GunflashFxPtrs;
  std::uint8_t m_FiringRateMultiplier;
  std::uint32_t m_FireMissilePressedTime;
  CEntity* m_pLastMissileTarget;
  std::uint32_t m_LastHSMissileLOSTime : 31;
  std::uint32_t m_bLastHSMissileLOS : 1;
  void* m_fxSysNozzle[4];
  void* m_fxSysFire;
  std::int32_t m_fireTime;
  bool m_fxActive;
};