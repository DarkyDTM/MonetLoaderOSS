#pragma once
#include "CPhysical.h"

enum eObjectType {
  OBJECT_MISSION = 2,
  OBJECT_TEMPORARY = 3,
  OBJECT_MISSION2 = 6
};

struct CObject : public CPhysical {
  void* pControlCodeList;
  unsigned char nObjectType;
  unsigned char nBonusValue;
  unsigned short wCostValue;
  struct
  {
    unsigned int bIsPickUp : 1;
    unsigned int bNoPickUpEffects : 1;
    unsigned int bPickupPropertyForSale : 1;
    unsigned int bPickupInShopOutOfStock : 1;
    unsigned int bGlassBroken : 1;
    unsigned int bGlassBrokenAltogether : 1;
    unsigned int bIsExploded : 1;
    unsigned int bParentIsACar : 1;

    unsigned int bIsLampPost : 1;
    unsigned int bIsTargatable : 1;
    unsigned int bIsBroken : 1;
    unsigned int bTrainCrossEnabled : 1;
    unsigned int bIsPhotographed : 1;
    unsigned int bIsLiftable : 1;
    unsigned int bIsDoorMoving : 1;
    unsigned int bbIsDoorOpen : 1;

    unsigned int bHasNoModel : 1;
    unsigned int bIsScaled : 1;
    unsigned int bCanBeAttachedToMagnet : 1;
    unsigned int bLandedOnMovingCol : 1;
    unsigned int ScriptBrainStatus : 2;
    unsigned int bFadingIn : 1;
    unsigned int bAffectedByColBrightness : 1;

    unsigned int bDisableEnabledAttractors : 1;
    unsigned int bDoNotRender : 1;
  } nObjectFlags;
  unsigned char nColDamageEffect;
  unsigned char nStoredColDamageEffect;
  char field_146; // KeepieUppyCounter
  char nGarageDoorGarageIndex;
  unsigned char nLastWeaponDamage;
  unsigned char nDayBrightness : 4;
  unsigned char nNightBrightness : 4;
  short nRefModelIndex;
  unsigned char nCarColor[4];
  int dwRemovalTime;
  float fHealth;
  float fDoorStartAngle;
  float fScale;
  void* pObjectInfo;
  void* pFire;
  short wScriptTriggerIndex;
  const char* remapTxdName;
  void* pRemapTexture;
  void* pDummyObject;
  int dwBurnTime;
  float fBurnDamage;
};