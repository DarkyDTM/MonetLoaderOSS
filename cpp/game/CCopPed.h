#pragma once
#include "CPed.h"

enum eCopType {
  COP_TYPE_CITYCOP,
  COP_TYPE_LAPDM1,
  COP_TYPE_SWAT1,
  COP_TYPE_SWAT2,
  COP_TYPE_FBI,
  COP_TYPE_ARMY,
  COP_TYPE_CSHER = 7
};

struct CCopPed : public CPed {
  bool bRoadBlockCop;
  bool bRemoveIfNonVisible;
  unsigned int copType;
  int nStuckCounter;
  CCopPed* pCopPartner;
  CPed* apCriminalsToKill[5];
  bool bIAmDriver;
};