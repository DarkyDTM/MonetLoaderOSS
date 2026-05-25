#pragma once
#include "CAEAudioEntity.h"
#include "CAETwinLoopSoundEntity.h"

struct tEngineSound {
  short nIndex;
  CAESound* pSound;
};

struct tVehicleAudioSettings {
  std::int8_t VehicleAudioType;
  std::int16_t PlayerBank;
  std::int16_t DummyBank;
  std::int8_t BassSetting;
  float BassFactor;
  float EnginePitch;
  std::int8_t HornType;
  float HornPitch;
  std::int8_t DoorType;
  std::int8_t EngineUpgrade;
  std::int8_t RadioStation;
  std::int8_t RadioType;
  std::int8_t VehicleAudioTypeForName;
  float EngineVolumeOffset;
};

struct CAEVehicleAudioEntity : public CAEAudioEntity {
  std::int16_t m_nStallCounter;
  tVehicleAudioSettings m_VehicleAudioSetting;
  bool m_bInitialised;
  bool m_bPlayerDriven;
  bool m_bPlayerOnlyAttached;
  bool m_bPlayerDriverAboutToExit;
  bool m_bWreckedVehicle;
  std::int8_t m_State;
  std::uint8_t m_AudioGear;
  float m_CrzCount;
  bool m_bSingleGear;
  std::int16_t m_nRainHitCount;
  std::int16_t m_nStalledCount;
  std::uint32_t m_nSwapStalledTime;
  bool m_bSilentStalled;
  bool m_bHelicoptorDisabled;
  bool m_bHornOn;
  bool m_bSirenOn;
  bool m_bFastSirenOn;
  float m_HornVolume;
  bool m_bUsesSiren;
  std::uint32_t m_TimeSplashLastTriggered;
  std::uint32_t m_TimeBeforeAllowAccelerate;
  std::uint32_t m_TimeBeforeAllowCruise;
  float m_fEventVolume;
  std::int16_t m_DummyEngineBank;
  std::int16_t m_PlayerEngineBank;
  std::int16_t m_DummySlot;
  tEngineSound m_EngineSounds[12];
  std::uint32_t m_TimeLastServiced;
  std::int16_t m_ACPlayPositionThisFrame;
  std::int16_t m_ACPlayPositionLastFrame;
  std::int16_t m_FramesAgoACLooped;
  std::int16_t m_ACPlayPercentWhenStopped;
  std::uint32_t m_TimeACStopped;
  std::int16_t m_ACPlayPositionWhenStopped;
  std::int16_t m_SurfaceSoundID;
  CAESound* m_SurfaceSoundPtr;
  std::int16_t m_RoadNoiseSoundID;
  CAESound* m_RoadNoiseSoundPtr;
  std::int16_t m_FlatTyreSoundID;
  CAESound* m_FlatTyreSoundPtr;
  std::int16_t m_ReverseSoundID;
  CAESound* m_ReverseSoundPtr;
  std::int16_t m_HornSoundID;
  CAESound* m_HornSoundPtr;
  CAESound* m_SirenSoundPtr;
  CAESound* m_FastSirenSoundPtr;
  CAETwinLoopSoundEntity m_SkidSound;
  float m_CurrentRotorFrequency;
  float m_CurrentDummyEngineVolume;
  float m_CurrentDummyEngineFrequency;
  float m_fMovingPartSmoothedSpeed;
  float m_fFadeIn;
  float m_fFadeOut;
  bool m_bNitroOnLastFrame;
  float m_CurrentNitroRatio;
};