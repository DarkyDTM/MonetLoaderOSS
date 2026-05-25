#pragma once
#include "CAESound.h"

struct CAEAudioEntity {
  void** vtbl;
  CEntity* pEntity;
  CAESound tempSound;
};