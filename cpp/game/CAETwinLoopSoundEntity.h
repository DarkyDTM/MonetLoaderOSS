#pragma once
#include <cstdint>
#include "CAEAudioEntity.h"

struct CAETwinLoopSoundEntity : public CAEAudioEntity {
  std::int16_t m_BankSlotID;
  std::int16_t m_FirstSoundID;
  std::int16_t m_SecondSoundID;
  CAEAudioEntity* m_pAudioEntity;
  std::int16_t m_bCurrentlyInUse;
  std::int16_t m_nFirstLength;
  std::int16_t m_nSecondLength;
  std::uint16_t m_MinSwapTime;
  std::uint16_t m_MaxSwapTime;
  std::uint32_t m_SwapTime;
  bool m_bPlayingFirst;
  std::int16_t m_StartPercentFirst;
  std::int16_t m_StartPercentSecond;
  CAESound* m_pFirstSoundPtr;
  CAESound* m_pSecondSoundPtr;
};