#pragma once
#include "CEntity.h"
#include "CQuaternion.h"

struct CPhysical : public CEntity {
  float m_fPrevDistFromCam;
  unsigned int m_nLastCollisionTime;

  struct {
    unsigned int bExtraHeavy : 1;
    unsigned int bApplyGravity : 1;
    unsigned int bDisableCollisionForce : 1;
    unsigned int bCollidable : 1;
    unsigned int bDisableTurnForce : 1;
    unsigned int bDisableMoveForce : 1;
    unsigned int bInfiniteMass : 1;
    unsigned int bDisableZ : 1;

    unsigned int bSubmergedInWater : 1;
    unsigned int bOnSolidSurface : 1;
    unsigned int bBroken : 1;
    unsigned int bTrainForceCol : 1;
    unsigned int bSkipLineCol : 1;
    unsigned int bDontApplySpeed : 1;
    unsigned int bDontLoadCollision : 1;
    unsigned int bHalfSpeedCollision : 1;

    unsigned int bForceHitReturnFalse : 1;
    unsigned int bDontProcessCollisionOurSelves : 1;
    unsigned int bBulletProof : 1;
    unsigned int bFireProof : 1;
    unsigned int bCollisionProof : 1;
    unsigned int bMeleeProof : 1;
    unsigned int bInvulnerable : 1;
    unsigned int bExplosionProof : 1;

    unsigned int bFlyer : 1;
    unsigned int bAttachedToEntity : 1;
    unsigned int bUsingSpecialColModel : 1;
    unsigned int bTouchingWater : 1;
    unsigned int bCanBeCollidedWith : 1;
    unsigned int bDestroyed : 1;
    unsigned int bDoorHitEndStop : 1;
    unsigned int bCarriedByRope : 1;
  } m_nPhysicalFlags;

  CVector m_vecMoveSpeed;
  CVector m_vecTurnSpeed;
  CVector m_vecFrictionMoveSpeed;
  CVector m_vecFrictionTurnSpeed;
  CVector m_vecForce;
  CVector m_vecTorque;
  float m_fMass;
  float m_fTurnMass;
  float m_fVelocityFrequency;
  float m_fAirResistance;
  float m_fElasticity;
  float m_fBuoyancyConstant;
  CVector m_vecCentreOfMass;
  void* m_pCollisionList;
  void* m_pMovingList;
  char field_B8;
  unsigned char m_nNumEntitiesCollided;
  unsigned char m_nContactSurface;
  char m_nNoOfStaticFrames;
  CEntity* m_apCollidedEntities[6];
  float m_fMovingSpeed; // ref @ CTheScripts::IsVehicleStopped
  float m_fDamageIntensity;
  CEntity* m_pDamageEntity;
  CVector m_vecLastCollisionImpactVelocity;
  CVector m_vecLastCollisionPosn;
  unsigned short m_nPieceType;
  CEntity* m_pAttachedTo;
  CVector m_vecAttachOffset;
  CVector m_vecAttachedEntityPosn;
  CQuaternion m_qAttachedEntityRotation;
  CEntity* m_pEntityIgnoredCollision;
  float m_fContactSurfaceBrightness;
  float m_fDynamicLighting;
  void* m_pShadowData;
};