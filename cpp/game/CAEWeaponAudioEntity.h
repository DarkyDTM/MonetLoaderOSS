#pragma once
#include "CAEAudioEntity.h"
struct CPed;

struct CAEWeaponAudioEntity : public CAEAudioEntity {
  bool m_bMiniGunSpinActive;
  bool m_bMiniGunFireActive;
  std::int8_t m_nLastWeaponPlaneFrequencyIndex;
  std::int8_t m_nMiniGunState;
  std::int8_t m_nChainsawState;
  std::uint32_t m_nLastFlameThrowerFireTimeMs;
  std::uint32_t m_nLastSprayCanFireTimeMs;
  std::uint32_t m_nLastFireExtFireTimeMs;
  std::uint32_t m_nLastMiniGunFireTimeMs;
  std::uint32_t m_nLastChainsawEventTimeMs;
  std::uint32_t m_nLastGunFireTimeMs;
  CAESound* m_pFlameThrowerIdleGasLoopSound;
};

struct CAEPedWeaponAudioEntity : public CAEWeaponAudioEntity {
  bool m_bInitialised;
  CPed* m_pParentPed;
};