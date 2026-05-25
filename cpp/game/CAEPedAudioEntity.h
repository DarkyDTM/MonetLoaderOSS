#pragma once
#include "CAEAudioEntity.h"
#include "CAETwinLoopSoundEntity.h"

struct CPed;
struct CAEPedAudioEntity : public CAEAudioEntity {
  bool m_bInitialised;
  short m_nLastSwimSplashSoundID;
  unsigned int m_nLastSwimWakeTriggerTimeMs;
  float m_fCurrentJetPackThrustVolume;
  float m_fCurrentJetPackGasVolume;
  float m_fCurrentJetPackRoarVolume;
  float m_fCurrentJetPackRoarFrequency;
  CPed* m_pParentPed;
  bool m_bJetPackOn;
  CAESound* m_pJetPackThrustSound;
  CAESound* m_pJetPackGasSound;
  CAESound* m_pJetPackRoarSound;
  CAETwinLoopSoundEntity m_ShirtFlapTwinLoopSound;
  CAESound* m_pWindRushSound;
  float m_fCurrentWindRushVolume;
  float m_fCurrentShirtFlapVolume;
};