#pragma once
#include "CAEPedAudioEntity.h"
#include "CAEPedSpeechAudioEntity.h"
#include "CAEWeaponAudioEntity.h"
#include "CEntity.h"
#include "CPedIK.h"
#include "CPedMisc.h"
#include "CPhysical.h"
#include "CPlayerData.h"
#include "CStoredCollPoly.h"
#include "CWeapon.h"

struct CVehicle;
struct CPed : public CPhysical {
  CAEPedAudioEntity m_pedAudio;
  CAEPedSpeechAudioEntity m_pedSpeech;
  CAEPedWeaponAudioEntity m_weaponAudio;
  CPedIntelligence* m_pIntelligence;
  CPlayerData* m_pPlayerData;
  unsigned char m_nCreatedBy;
  ePedState m_nPedState; // see ePedState
  int m_nMoveState; // see eMoveState
  CStoredCollPoly m_storedCollPoly;
  float m_fDistTravelledSinceLastHeightCheck;
  struct {
    unsigned int bIsStanding : 1; // is ped standing on something
    unsigned int bWasStanding : 1; // was ped standing on something
    unsigned int bIsLooking : 1; // is ped looking at something or in a direction
    unsigned int bIsRestoringLook : 1; // is ped restoring head postion from a look
    unsigned int bIsAimingGun : 1; // is ped aiming gun
    unsigned int bIsRestoringGun : 1; // is ped moving gun back to default posn
    unsigned int bCanPointGunAtTarget : 1; // can ped point gun at target
    unsigned int bIsTalking : 1; // is ped talking(see Chat())

    unsigned int bInVehicle : 1; // is in a vehicle
    unsigned int bIsInTheAir : 1; // is in the air
    unsigned int bIsLanding : 1; // is landing after being in the air
    unsigned int bHitSomethingLastFrame : 1; // has been in a collision last fram
    unsigned int bIsNearCar : 1; // has been in a collision last fram
    unsigned int bRenderPedInCar : 1; // has been in a collision last fram
    unsigned int bUpdateAnimHeading : 1; // update ped heading due to heading change during anim sequence
    unsigned int bRemoveHead : 1; // waiting on AntiSpazTimer to remove head

    unsigned int bFiringWeapon : 1; // is pulling trigger
    unsigned int bHasACamera : 1; // does ped possess a camera to document accidents
    unsigned int bPedIsBleeding : 1; // Ped loses a lot of blood if true
    unsigned int bStopAndShoot : 1; // Ped cannot reach target to attack with fist, need to use gun
    unsigned int bIsPedDieAnimPlaying : 1; // is ped die animation finished so can dead now
    unsigned int bStayInSamePlace : 1; // when set, ped stays put
    unsigned int bKindaStayInSamePlace : 1; // when set, ped doesn't seek out opponent or cover large distances. Will still shuffle and look for cover
    unsigned int bBeingChasedByPolice : 1; // use nodes for routefind

    unsigned int bNotAllowedToDuck : 1; // Is this ped allowed to duck at all?
    unsigned int bCrouchWhenShooting : 1; // duck behind cars etc
    unsigned int bIsDucking : 1; // duck behind cars etc
    unsigned int bGetUpAnimStarted : 1; // don't want to play getup anim if under something
    unsigned int bDoBloodyFootprints : 1; // unsigned int bIsLeader :1;
    unsigned int bDontDragMeOutCar : 1;
    unsigned int bStillOnValidPoly : 1; // set if the polygon the ped is on is still valid for collision
    unsigned int bAllowMedicsToReviveMe : 1;

    unsigned int bResetWalkAnims : 1;
    unsigned int bOnBoat : 1; // flee but only using nodes
    unsigned int bBusJacked : 1; // flee but only using nodes
    unsigned int bFadeOut : 1; // set if you want ped to fade out
    unsigned int bKnockedUpIntoAir : 1; // has ped been knocked up into the air by a car collision
    unsigned int bHitSteepSlope : 1; // has ped collided/is standing on a steep slope (surface type)
    unsigned int bCullExtraFarAway : 1; // special ped only gets culled if it's extra far away (for roadblocks)
    unsigned int bTryingToReachDryLand : 1; // has ped just exited boat and trying to get to dry land

    unsigned int bCollidedWithMyVehicle : 1;
    unsigned int bRichFromMugging : 1; // ped has lots of cash cause they've been mugging people
    unsigned int bChrisCriminal : 1; // Is a criminal as killed during Chris' police mission (should be counted as such)
    unsigned int bShakeFist : 1; // test shake hand at look entity
    unsigned int bNoCriticalHits : 1; // ped cannot be killed by a single bullet
    unsigned int bHasAlreadyBeenRecorded : 1; // Used for replays
    unsigned int bUpdateMatricesRequired : 1; // if PedIK has altered bones so matrices need updated this frame
    unsigned int bFleeWhenStanding : 1; //

    unsigned int bMiamiViceCop : 1; //
    unsigned int bMoneyHasBeenGivenByScript : 1; //
    unsigned int bHasBeenPhotographed : 1; //
    unsigned int bIsDrowning : 1;
    unsigned int bDrownsInWater : 1;
    unsigned int bHeadStuckInCollision : 1;
    unsigned int bDeadPedInFrontOfCar : 1;
    unsigned int bStayInCarOnJack : 1;

    unsigned int bDontFight : 1;
    unsigned int bDoomAim : 1;
    unsigned int bCanBeShotInVehicle : 1;
    unsigned int bPushedAlongByCar : 1; // ped is getting pushed along by car collision (so don't take damage from horz velocity)
    unsigned int bNeverEverTargetThisPed : 1;
    unsigned int bThisPedIsATargetPriority : 1;
    unsigned int bCrouchWhenScared : 1;
    unsigned int bKnockedOffBike : 1;

    unsigned int bDonePositionOutOfCollision : 1;
    unsigned int bDontRender : 1;
    unsigned int bHasBeenAddedToPopulation : 1;
    unsigned int bHasJustLeftCar : 1;
    unsigned int bIsInDisguise : 1;
    unsigned int bDoesntListenToPlayerGroupCommands : 1;
    unsigned int bIsBeingArrested : 1;
    unsigned int bHasJustSoughtCover : 1;

    unsigned int bKilledByStealth : 1;
    unsigned int bDoesntDropWeaponsWhenDead : 1;
    unsigned int bCalledPreRender : 1;
    unsigned int bBloodPuddleCreated : 1; // Has a static puddle of blood been created yet
    unsigned int bPartOfAttackWave : 1;
    unsigned int bClearRadarBlipOnDeath : 1;
    unsigned int bNeverLeavesGroup : 1; // flag that we want to test 3 extra spheres on col model
    unsigned int bTestForBlockedPositions : 1; // this sets these indicator flags for various posisions on the front of the ped

    unsigned int bRightArmBlocked : 1;
    unsigned int bLeftArmBlocked : 1;
    unsigned int bDuckRightArmBlocked : 1;
    unsigned int bMidriffBlockedForJump : 1;
    unsigned int bFallenDown : 1;
    unsigned int bUseAttractorInstantly : 1;
    unsigned int bDontAcceptIKLookAts : 1;
    unsigned int bHasAScriptBrain : 1;

    unsigned int bWaitingForScriptBrainToLoad : 1;
    unsigned int bHasGroupDriveTask : 1;
    unsigned int bCanExitCar : 1;
    unsigned int CantBeKnockedOffBike : 2; // 0=Default(harder for mission peds) 1=Never 2=Always normal(also for mission peds)
    unsigned int bHasBeenRendered : 1;
    unsigned int bIsCached : 1;
    unsigned int bPushOtherPeds : 1; // GETS RESET EVERY FRAME - SET IN TASK: want to push other peds around (eg. leader of a group or ped trying to get in a car)

    unsigned int bHasBulletProofVest : 1;
    unsigned int bUsingMobilePhone : 1;
    unsigned int bUpperBodyDamageAnimsOnly : 1;
    unsigned int bStuckUnderCar : 1;
    unsigned int bKeepTasksAfterCleanUp : 1; // If true ped will carry on with task even after cleanup
    unsigned int bIsDyingStuck : 1;
    unsigned int bIgnoreHeightCheckOnGotoPointTask : 1; // set when walking round buildings, reset when task quits
    unsigned int bForceDieInCar : 1;

    unsigned int bCheckColAboveHead : 1;
    unsigned int bIgnoreWeaponRange : 1;
    unsigned int bDruggedUp : 1;
    unsigned int bWantedByPolice : 1; // if this is set, the cops will always go after this ped when they are doing a KillCriminal task
    unsigned int bSignalAfterKill : 1;
    unsigned int bCanClimbOntoBoat : 1;
    unsigned int bPedHitWallLastFrame : 1; // useful to store this so that AI knows (normal will still be available)
    unsigned int bIgnoreHeightDifferenceFollowingNodes : 1;

    unsigned int bMoveAnimSpeedHasBeenSetByTask : 1;
    unsigned int bGetOutUpsideDownCar : 1;
    unsigned int bJustGotOffTrain : 1;
    unsigned int bDeathPickupsPersist : 1;
    unsigned int bTestForShotInVehicle : 1;
    unsigned int bUsedForReplay : 1; // This ped is controlled by replay and should be removed when replay is done.
  } m_nPedFlags;
  AnimBlendFrameData* m_apBones[19];
  unsigned int m_nAnimGroup;
  CVector2D m_vecAnimMovingShiftLocal;
  CPedAcquaintance m_acquaintance;
  void* m_pWeaponObject;
  void* m_pGunflashObject;
  void* m_pGogglesObject;
  unsigned char* m_pGogglesState;
  short m_nWeaponGunflashAlphaMP1;
  short field_506;
  short m_nWeaponGunflashAlphaMP2;
  short field_50A;
  CPedIK m_pedIK;
  int field_52C;
  int field_538;
  int field_53C;
  float m_fHealth;
  float m_fMaxHealth;
  float m_fArmour;
  int field_54C;
  CVector2D m_vecAnimMovingShift;
  float m_fCurrentRotation;
  float m_fAimingRotation;
  float m_fHeadingChangeRate;
  float m_fHeadingChangeRateAccel;
  CPhysical* m_pGroundPhysical;
  CVector m_vecGroundOffset;
  CVector m_vecGroundNormal;
  CEntity* m_pContactEntity;
  float field_588;
  CVehicle* m_pVehicle;
  CVehicle* m_pMyAccidentVehicle;
  void* m_pAccident;
  int m_nPedType; // see ePedType
  void* m_pStats;
  CWeapon m_aWeapons[13];
  eWeaponType m_nSavedWeapon; // when we need to hide ped weapon, we save it temporary here
  eWeaponType m_nDelayedWeapon; // 'delayed' weapon is like an additional weapon, f.e., simple cop has a nitestick as current and pistol as delayed weapons
  unsigned int m_nDelayedWeaponAmmo;
  unsigned char m_nActiveWeaponSlot;
  unsigned char m_nWeaponShootingRate;
  unsigned char m_nWeaponAccuracy;
  CEntity* m_pTargetedObject;
  CEntity* m_pEntMagnetizeTarget;
  CVector m_vecWeaponPrevPos;
  char m_nWeaponSkill;
  char m_nFightingStyle; // see eFightingStyle
  char m_nAllowedAttackMoves;
  char field_72F;
  void* m_pFire;
  float m_fFireDamageMultiplier;
  CEntity* m_pEntLookEntity;
  float m_fLookHeading;
  int m_nWeaponModelId;
  unsigned int m_nUnconsciousTimer;
  unsigned int m_nLookTimer;
  unsigned int m_nAttackTimer;
  unsigned int nDeathTime;
  char m_nBodypartToRemove;
  short m_nMoneyCount;
  float m_fWobble;
  float m_fWobbleSpeed;
  char m_nLastWeaponDamage;
  CEntity* m_pLastEntityDamage;
  int field_768;
  CVector m_vecTurretOffset;
  float m_fTurretAngleA;
  float m_fTurretAngleB;
  int m_nTurretPosnMode;
  int m_nTurretAmmo;
  void* m_pCoverPoint; // CCoverPoint *
  void* m_pEnex; // CEnEx *
  float m_fRemovalDistMultiplier; // 1.0 by default
  short m_nSpecialModelIndex;
  unsigned int nLastTalkSfx;
};