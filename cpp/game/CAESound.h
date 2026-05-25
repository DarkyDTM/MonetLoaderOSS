#pragma once
#include "CVector.h"

enum eSoundEnvironment {
  SOUND_FRONT_END = 1,
  SOUND_UNCANCELLABLE = 2,
  SOUND_REQUEST_UPDATES = 4,
  SOUND_PLAY_PHYSICALLY = 8,
  SOUND_UNPAUSABLE = 16,
  SOUND_START_PERCENTAGE = 32,
  SOUND_MUSIC_MASTERED = 64,
  SOUND_LIFESPAN_TIED_TO_PHYSICAL_ENTITY = 128,
  SOUND_UNDUCKABLE = 256,
  SOUND_UNCOMPRESSABLE = 512,
  SOUND_ROLLED_OFF = 1024,
  SOUND_SMOOTH_DUCKING = 2048,
  SOUND_FORCED_FRONT = 4096
};

struct CAEAudioEntity;
struct CEntity;

struct CAESound {
  short nBankSlotId;
  short nSoundIdInSlot;
  CAEAudioEntity* pBaseAudio;
  CEntity* pPhysicalEntity;
  unsigned int nEvent;
  float fMaxVolume;
  float fVolume;
  float fSoundDistance;
  float fSpeed;
  float fFrequencyVariance;
  CVector vecCurrPosn;
  CVector vecPrevPosn;
  unsigned int nLastFrameUpdate;
  unsigned int nCurrTimeUpdate;
  unsigned int nPrevTimeUpdate;
  float fCurrCamDist;
  float fPrevCamDist;
  float fDoppler;
  unsigned char field_54; // uint8 m_FrameDelay
  union {
    unsigned short nEnvironmentFlags;
    struct
    {
      unsigned short bFrontEnd : 1;
      unsigned short bUncancellable : 1;
      unsigned short bRequestUpdates : 1;
      unsigned short bPlayPhysically : 1;
      unsigned short bUnpausable : 1;
      unsigned short bStartPercentage : 1;
      unsigned short bMusicMastered : 1;
      unsigned short bLifespanTiedToPhysicalEntity : 1;
      unsigned short bUndackable : 1;
      unsigned short bUncompressable : 1;
      unsigned short bRolledOff : 1;
      unsigned short bSmoothDucking : 1;
      unsigned short bForcedFront : 1;
    };
  };
  unsigned short nIsUsed;
  short bAudioHardwareAware;
  short nCurrentPlayPosition;
  short bPhysicallyPlaying;
  float fFinalVolume;
  float fFrequency;
  short bRequestedStopped;
  float fSoundHeadRoom;
  short nLength;
};