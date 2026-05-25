#pragma once
#include "lib_manager.h"
#include "CControllerState.h"

struct CPad
{
  CControllerState NewState;
  CControllerState OldState;
  int currentPadId;
  std::int16_t SteeringLeftRightBuffer[10];
  std::int32_t DrunkDrivingBufferUsed;
  CControllerState PCTempKeyState;
  CControllerState PCTempJoyState;
  CControllerState PCTempMouseState;
  std::uint8_t Phase;
  std::int16_t ShakeDur;
  std::uint16_t DisablePlayerControls;
  std::uint8_t ShakeFreq;
  std::uint8_t JustOutOfFrontEnd;
  float fCruisingSpeed;
  bool bRhythm;
  bool bWheelie;
  bool bStoppie;
  bool bApplyGas;
  bool bApplyBrake;
  bool bLaneCorrection;
  bool bUsingDebugCamera;
  bool bUsingDebugPlayerFreeze;
  bool bHasCheated;
  bool bDisableForbiddenTerr;
  bool bStopRhythmSprites;
  bool bDoorsLocked;
  bool bRegainControl;
  float fBikeStickY;
  bool bApplyBrakes;
  bool bDisablePlayerEnterCar;
  bool bDisablePlayerDuck;
  bool bDisablePlayerFireWeapon;
  bool bDisablePlayerFireWeaponWithL1;
  bool bDisablePlayerCycleWeapon;
  bool bDisablePlayerJump;
  bool bDisablePlayerDisplayVitalStats;
  std::uint32_t LastTimeTouched;
  std::int32_t AverageWeapon;
  std::int32_t AverageEntries;
  std::uint32_t NoShakeBeforeThis;
  std::uint8_t NoShakeFreq;
  bool bHasJetPack;
  bool bRocketLocked;
  bool bTrainPassenger;
  bool bSavedForTrain;
  bool bSetSteeringMode;
  bool bSetTouchLayout;
  float m_fAccelX;
  float m_fAccelY;
  float m_fAccelZ;

  static CPad* GetPad(int id)
  {
    return &(reinterpret_cast<CPad*>(lib_manager::pads)[id]);
  }
};
