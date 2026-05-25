#pragma once
#include "CObject.h"
#include "CVector.h"

struct CCutsceneObject : public CObject {
  union {
    void* pAttachTo;
    unsigned int nAttachBone; // this one if m_pAttachmentObject != 0
  };
  CObject* pAttachmentObject;
  CVector vWorldPosition;
  CVector vForce;
};