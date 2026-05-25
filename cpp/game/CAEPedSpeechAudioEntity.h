#pragma once
#include "CAEAudioEntity.h"

enum eAudioPedType {
  PED_TYPE_GEN = 0,
  PED_TYPE_EMG = 1,
  PED_TYPE_PLAYER = 2,
  PED_TYPE_GANG = 3,
  PED_TYPE_GFD = 4,
  PED_TYPE_SPC = 5
};

struct CAEPedSpeechAudioEntity : public CAEAudioEntity {
  CAESound* SoundPtrs[5];
  bool b_Initialised;
  std::int16_t m_PedType;
  std::int16_t m_VoiceID;
  std::int16_t m_bFemale;
  bool m_bPlayingSpeech;
  bool m_bSpeechDisabled;
  bool m_bSpeechDisabledForScriptSpeech;
  bool m_bFrontEnd;
  bool m_bForceAudible;
  CAESound* m_pSound;
  std::int16_t m_SoundID;
  std::int16_t m_BankID;
  std::int16_t m_PedSpeechSlotID;
  float m_fEventVolume;
  std::int16_t m_LastUsedGlobalSpeechContext;
  std::uint32_t m_NextTimeCanSayPain[19];
};