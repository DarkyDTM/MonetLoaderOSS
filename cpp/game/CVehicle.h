#pragma once
#include "CAEVehicleAudioEntity.h"
#include "CAutoPilot.h"
#include "CPhysical.h"
#include "CStoredCollPoly.h"
#include "handling.h"

struct CPed;
struct CVehicle : public CPhysical {
  CAEVehicleAudioEntity m_vehicleAudio;
  tHandlingData* m_pHandlingData;
  tFlyingHandlingData* m_pFlyingHandlingData;
  union {
    eVehicleHandlingFlags m_nHandlingFlagsIntValue;
    struct {
      unsigned int b1gBoost : 1;
      unsigned int b2gBoost : 1;
      unsigned int bNpcAntiRoll : 1;
      unsigned int bNpcNeutralHandl : 1;
      unsigned int bNoHandbrake : 1;
      unsigned int bSteerRearwheels : 1;
      unsigned int bHbRearwheelSteer : 1;
      unsigned int bAltSteerOpt : 1;
      unsigned int bWheelFNarrow2 : 1;
      unsigned int bWheelFNarrow : 1;
      unsigned int bWheelFWide : 1;
      unsigned int bWheelFWide2 : 1;
      unsigned int bWheelRNarrow2 : 1;
      unsigned int bWheelRNarrow : 1;
      unsigned int bWheelRWide : 1;
      unsigned int bWheelRWide2 : 1;
      unsigned int bHydraulicGeom : 1;
      unsigned int bHydraulicInst : 1;
      unsigned int bHydraulicNone : 1;
      unsigned int bNosInst : 1;
      unsigned int bOffroadAbility : 1;
      unsigned int bOffroadAbility2 : 1;
      unsigned int bHalogenLights : 1;
      unsigned int bProcRearwheelFirst : 1;
      unsigned int bUseMaxspLimit : 1;
      unsigned int bLowRider : 1;
      unsigned int bStreetRacer : 1;
      unsigned int bUnused1 : 1;
      unsigned int bSwingingChassis : 1;
    } m_nHandlingFlags;
  };
  CAutoPilot m_autoPilot;
  struct {
    unsigned char bIsLawEnforcer : 1; // Is this guy chasing the player at the moment
    unsigned char bIsAmbulanceOnDuty : 1; // Ambulance trying to get to an accident
    unsigned char bIsFireTruckOnDuty : 1; // Firetruck trying to get to a fire
    unsigned char bIsLocked : 1; // Is this guy locked by the script (cannot be removed)
    unsigned char bEngineOn : 1; // For sound purposes. Parked cars have their engines switched off (so do destroyed cars)
    unsigned char bIsHandbrakeOn : 1; // How's the handbrake doing ?
    unsigned char bLightsOn : 1; // Are the lights switched on ?
    unsigned char bFreebies : 1; // Any freebies left in this vehicle ?

    unsigned char bIsVan : 1; // Is this vehicle a van (doors at back of vehicle)
    unsigned char bIsBus : 1; // Is this vehicle a bus
    unsigned char bIsBig : 1; // Is this vehicle a bus
    unsigned char bLowVehicle : 1; // Need this for sporty type cars to use low getting-in/out anims
    unsigned char bComedyControls : 1; // Will make the car hard to control (hopefully in a funny way)
    unsigned char bWarnedPeds : 1; // Has scan and warn peds of danger been processed?
    unsigned char bCraneMessageDone : 1; // A crane message has been printed for this car allready
    unsigned char bTakeLessDamage : 1; // This vehicle is stronger (takes about 1/4 of damage)

    unsigned char bIsDamaged : 1; // This vehicle has been damaged and is displaying all its components
    unsigned char bHasBeenOwnedByPlayer : 1; // To work out whether stealing it is a crime
    unsigned char bFadeOut : 1; // Fade vehicle out
    unsigned char bIsBeingCarJacked : 1; // Fade vehicle out
    unsigned char bCreateRoadBlockPeds : 1; // If this vehicle gets close enough we will create peds (coppers or gang members) round it
    unsigned char bCanBeDamaged : 1; // Set to FALSE during cut scenes to avoid explosions
    unsigned char bOccupantsHaveBeenGenerated : 1; // Is true if the occupants have already been generated. (Shouldn't happen again)
    unsigned char bGunSwitchedOff : 1; // Level designers can use this to switch off guns on boats

    unsigned char bVehicleColProcessed : 1; // Has ProcessEntityCollision been processed for this car?
    unsigned char bIsCarParkVehicle : 1; // Car has been created using the special CAR_PARK script command
    unsigned char bHasAlreadyBeenRecorded : 1; // Used for replays
    unsigned char bPartOfConvoy : 1;
    unsigned char bHeliMinimumTilt : 1; // This heli should have almost no tilt really
    unsigned char bAudioChangingGear : 1; // sounds like vehicle is changing gear
    unsigned char bIsDrowning : 1; // is vehicle occupants taking damage in water (i.e. vehicle is dead in water)
    unsigned char bTyresDontBurst : 1; // If this is set the tyres are invincible

    unsigned char bCreatedAsPoliceVehicle : 1; // True if this guy was created as a police vehicle (enforcer, policecar, miamivice car etc)
    unsigned char bRestingOnPhysical : 1; // Dont go static cause car is sitting on a physical object that might get removed
    unsigned char bParking : 1;
    unsigned char bCanPark : 1;
    unsigned char bFireGun : 1; // Does the ai of this vehicle want to fire it's gun?
    unsigned char bDriverLastFrame : 1; // Was there a driver present last frame ?
    unsigned char bNeverUseSmallerRemovalRange : 1; // Some vehicles (like planes) we don't want to remove just behind the camera.
    unsigned char bIsRCVehicle : 1; // Is this a remote controlled (small) vehicle. True whether the player or AI controls it.

    unsigned char bAlwaysSkidMarks : 1; // This vehicle leaves skidmarks regardless of the wheels' states.
    unsigned char bEngineBroken : 1; // Engine doesn't work. Player can get in but the vehicle won't drive
    unsigned char bVehicleCanBeTargetted : 1; // The ped driving this vehicle can be targetted, (for Torenos plane mission)
    unsigned char bPartOfAttackWave : 1; // This car is used in an attack during a gang war
    unsigned char bWinchCanPickMeUp : 1; // This car cannot be picked up by any ropes.
    unsigned char bImpounded : 1; // Has this vehicle been in a police impounding garage
    unsigned char bVehicleCanBeTargettedByHS : 1; // Heat seeking missiles will not target this vehicle.
    unsigned char bSirenOrAlarm : 1; // Set to TRUE if siren or alarm active, else FALSE

    unsigned char bHasGangLeaningOn : 1;
    unsigned char bGangMembersForRoadBlock : 1; // Will generate gang members if NumPedsForRoadBlock > 0
    unsigned char bDoesProvideCover : 1; // If this is false this particular vehicle can not be used to take cover behind.
    unsigned char bMadDriver : 1; // This vehicle is driving like a lunatic
    unsigned char bUpgradedStereo : 1; // This vehicle has an upgraded stereo
    unsigned char bConsideredByPlayer : 1; // This vehicle is considered by the player to enter
    unsigned char bPetrolTankIsWeakPoint : 1; // If false shootong the petrol tank will NOT Blow up the car
    unsigned char bDisableParticles : 1; // Disable particles from this car. Used in garage.

    unsigned char bHasBeenResprayed : 1; // Has been resprayed in a respray garage. Reset after it has been checked.
    unsigned char bUseCarCheats : 1; // If this is true will set the car cheat stuff up in ProcessControl()
    unsigned char bDontSetColourWhenRemapping : 1; // If the texture gets remapped we don't want to change the colour with it.
    unsigned char bUsedForReplay : 1; // This car is controlled by replay and should be removed when replay is done.
  } m_nVehicleFlags;
  unsigned int m_nCreationTime;
  uint8_t m_nPrimaryColor;
  uint8_t m_nSecondaryColor;
  uint8_t m_nTertiaryColor;
  uint8_t m_nQuaternaryColor;
  char m_anExtras[2];
  short m_anUpgrades[15];
  float m_fWheelScale;
  unsigned short m_nAlarmState;
  short m_nForcedRandomRouteSeed; // if this is non-zero the random wander gets deterministic
  CPed* m_pDriver;
  CPed* m_apPassengers[8];
  unsigned char m_nNumPassengers;
  unsigned char m_nNumGettingIn;
  unsigned char m_nGettingInFlags;
  unsigned char m_nGettingOutFlags;
  unsigned char m_nMaxPassengers;
  unsigned char m_nWindowsOpenFlags; // initialised, but not used?
  unsigned char m_nNitroBoosts;
  unsigned char m_nSpecialColModel;
  CEntity* m_pEntityWeAreOn; // we get it from CWorld::ProcessVerticalLine or ProcessEntityCollision, it's entity under us,
                             // only static entities (buildings or roads)
  void* m_pFire;
  float m_fSteerAngle;
  float m_f2ndSteerAngle; // used for steering 2nd set of wheels or elevators etc..
  float m_fGasPedal;
  float m_fBreakPedal;
  unsigned char m_nCreatedBy; // see eVehicleCreatedBy
  float m_fCachedTotalSteer;
  short m_nExtendedRemovalRange; // when game wants to delete a vehicle, it gets min(m_wExtendedRemovalRange, 170.0)
  unsigned char m_nBombOnBoard : 3; // 0 = None
                                    // 1 = Timed
                                    // 2 = On ignition
                                    // 3 = remotely set ?
                                    // 4 = Timed Bomb has been activated
                                    // 5 = On ignition has been activated
  unsigned char m_nOverrideLights : 2; // uses enum NO_CAR_LIGHT_OVERRIDE, FORCE_CAR_LIGHTS_OFF, FORCE_CAR_LIGHTS_ON
  unsigned char m_nWinchType : 2; // Does this vehicle use a winch?
  unsigned char m_nGunsCycleIndex : 2; // Cycle through alternate gun hardpoints on planes/helis
  unsigned char m_nOrdnanceCycleIndex : 2; // Cycle through alternate ordnance hardpoints on planes/helis
  unsigned char m_nUsedForCover; // Has n number of cops hiding/attempting to hid behind it
  unsigned char m_nAmmoInClip; // Used to make the guns on boat do a reload (20 by default).
  unsigned char m_nPacMansCollected; // initialised, but not used?
  unsigned char m_nPedsPositionForRoadBlock; // 0, 1 or 2
  unsigned char m_nNumCopsForRoadBlock;
  float m_fDirtLevel; // Dirt level of vehicle body texture: 0.0f=fully clean, 15.0f=maximum dirt visible
  unsigned char m_nCurrentGear;
  float m_fGearChangeCount; // used as parameter for cTransmission::CalculateDriveAcceleration, but doesn't change
  float m_fWheelSpinForAudio;
  float m_fHealth;
  CVehicle* m_pTractor;
  CVehicle* m_pTrailer;
  bool m_bFireAutoFlare;
  CPed* m_pWhoInstalledBombOnMe;
  unsigned int m_nTimeTillWeNeedThisCar; // game won't try to delete this car while this time won't reach
  unsigned int m_nGunFiringTime; // last time when gun on vehicle was fired (used on boats)
  unsigned int m_nTimeWhenBlowedUp; // game will delete vehicle when 60 seconds after this time will expire
  short m_nCopsInCarTimer; // timer for police car (which is following player) occupants to stay in car. If this timer reachs
                           // some value, they will leave a car. The timer increases each frame if player is stopped in car,
                           // otherway it resets
  short m_wBombTimer; // goes down with each frame
  CPed* m_pWhoDetonatedMe; // if vehicle was detonated, game copies m_pWhoInstalledBombOnMe here
  float m_fVehicleFrontGroundZ; // we get these values from CCollision::IsStoredPolyStillValidVerticalLine
  float m_fVehicleRearGroundZ; // or CWorld::ProcessVerticalLine
  char m_nNumOilSpillsToDo;
  float m_fOilSpillLastX;
  float m_fOilSpillLastY;
  unsigned int m_nDoorLock; // see enum eCarLock
  unsigned int m_nProjectileWeaponFiringTime; // manual-aimed projectiles for hunter, lock-on projectile for hydra
  unsigned int m_nAdditionalProjectileWeaponFiringTime; // manual-aimed projectiles for hydra
  unsigned int m_nTimeForMinigunFiring; // minigun on hunter
  unsigned char m_nLastWeaponDamageType; // see eWeaponType, -1 if no damage
  CEntity* m_pLastDamageEntity;
  char m_nRadioStation; // not used?
  char m_nRainHitCount; // initialised, but not used?
  char m_nSoundIndex; // initialised, but not used?
  char m_nVehicleWeaponInUse; // see enum eCarWeapon
  unsigned int m_nHornCounter;
  char m_nHornPattern; // random id related to siren
  char m_NoHornCount; // car horn related
  char m_nComedyControlsState;
  char m_nHasslePosId;
  CStoredCollPoly m_FrontCollPoly; // poly which is under front part of car
  CStoredCollPoly m_RearCollPoly; // poly which is under rear part of car
  unsigned char m_anCollisionLighting[4]; // left front, left rear, right front, right rear
  void* m_pOverheatParticle;
  void* m_pFireParticle;
  void* m_pDustParticle;
  union {
    unsigned char m_nRenderLightsFlags;
    struct {
      unsigned char m_bRightFront : 1;
      unsigned char m_bLeftFront : 1;
      unsigned char m_bRightRear : 1;
      unsigned char m_bLeftRear : 1;
    } m_renderLights;
  };
  void* m_pCustomCarPlate;
  float fSteer;
  unsigned int m_nVehicleClass; // see enum eVehicleClass
  unsigned int m_nVehicleSubClass;
  const char* m_previousRemapTxdName;
  const char* m_remapTxdName;
  void* m_pRemapTexture;
};