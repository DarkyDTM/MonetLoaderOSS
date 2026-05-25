#pragma once
#include "CEntityScanner.h"
#include "CVector.h"
#include "events.h"

struct CPed;

enum ePedBones {
  BONE_PELVIS1 = 1,
  BONE_PELVIS = 2,
  BONE_SPINE1 = 3,
  BONE_UPPERTORSO = 4,
  BONE_NECK = 5,
  BONE_HEAD2 = 6,
  BONE_HEAD1 = 7,
  BONE_HEAD = 8,
  BONE_RIGHTUPPERTORSO = 21,
  BONE_RIGHTSHOULDER = 22,
  BONE_RIGHTELBOW = 23,
  BONE_RIGHTWRIST = 24,
  BONE_RIGHTHAND = 25,
  BONE_RIGHTTHUMB = 26,
  BONE_LEFTUPPERTORSO = 31,
  BONE_LEFTSHOULDER = 32,
  BONE_LEFTELBOW = 33,
  BONE_LEFTWRIST = 34,
  BONE_LEFTHAND = 35,
  BONE_LEFTTHUMB = 36,
  BONE_LEFTHIP = 41,
  BONE_LEFTKNEE = 42,
  BONE_LEFTANKLE = 43,
  BONE_LEFTFOOT = 44,
  BONE_RIGHTHIP = 51,
  BONE_RIGHTKNEE = 52,
  BONE_RIGHTANKLE = 53,
  BONE_RIGHTFOOT = 54,
};

enum ePedState {
  PEDSTATE_NONE,
  PEDSTATE_IDLE,
  PEDSTATE_LOOK_ENTITY,
  PEDSTATE_LOOK_HEADING,
  PEDSTATE_WANDER_RANGE,
  PEDSTATE_WANDER_PATH,
  PEDSTATE_SEEK_POSITION,
  PEDSTATE_SEEK_ENTITY,
  PEDSTATE_FLEE_POSITION,
  PEDSTATE_FLEE_ENTITY,
  PEDSTATE_PURSUE,
  PEDSTATE_FOLLOW_PATH,
  PEDSTATE_SNIPER_MODE,
  PEDSTATE_ROCKETLAUNCHER_MODE,
  PEDSTATE_DUMMY,
  PEDSTATE_PAUSE,
  PEDSTATE_ATTACK,
  PEDSTATE_FIGHT,
  PEDSTATE_FACE_PHONE,
  PEDSTATE_MAKE_PHONECALL,
  PEDSTATE_CHAT,
  PEDSTATE_MUG,
  PEDSTATE_AIMGUN,
  PEDSTATE_AI_CONTROL,
  PEDSTATE_SEEK_CAR,
  PEDSTATE_SEEK_BOAT_POSITION,
  PEDSTATE_FOLLOW_ROUTE,
  PEDSTATE_CPR,
  PEDSTATE_SOLICIT,
  PEDSTATE_BUY_ICE_CREAM,
  PEDSTATE_INVESTIGATE_EVENT,
  PEDSTATE_EVADE_STEP,
  PEDSTATE_ON_FIRE,
  PEDSTATE_SUNBATHE,
  PEDSTATE_FLASH,
  PEDSTATE_JOG,
  PEDSTATE_ANSWER_MOBILE,
  PEDSTATE_HANG_OUT,
  PEDSTATE_STATES_NO_AI,
  PEDSTATE_ABSEIL_FROM_HELI,
  PEDSTATE_SIT,
  PEDSTATE_JUMP,
  PEDSTATE_FALL,
  PEDSTATE_GETUP,
  PEDSTATE_STAGGER,
  PEDSTATE_EVADE_DIVE,
  PEDSTATE_STATES_CAN_SHOOT,
  PEDSTATE_ENTER_TRAIN,
  PEDSTATE_EXIT_TRAIN,
  PEDSTATE_ARREST_PLAYER,
  PEDSTATE_DRIVING,
  PEDSTATE_PASSENGER,
  PEDSTATE_TAXI_PASSENGER,
  PEDSTATE_OPEN_DOOR,
  PEDSTATE_DIE,
  PEDSTATE_DEAD,
  PEDSTATE_DIE_BY_STEALTH,
  PEDSTATE_CARJACK,
  PEDSTATE_DRAGGED_FROM_CAR,
  PEDSTATE_ENTER_CAR,
  PEDSTATE_STEAL_CAR,
  PEDSTATE_EXIT_CAR,
  PEDSTATE_HANDS_UP,
  PEDSTATE_ARRESTED,
  PEDSTATE_DEPLOY_STINGER
};

enum ePedType : unsigned int {
  PED_TYPE_PLAYER1,
  PED_TYPE_PLAYER2,
  PED_TYPE_PLAYER_NETWORK,
  PED_TYPE_PLAYER_UNUSED,
  PED_TYPE_CIVMALE,
  PED_TYPE_CIVFEMALE,
  PED_TYPE_COP,
  PED_TYPE_GANG1,
  PED_TYPE_GANG2,
  PED_TYPE_GANG3,
  PED_TYPE_GANG4,
  PED_TYPE_GANG5,
  PED_TYPE_GANG6,
  PED_TYPE_GANG7,
  PED_TYPE_GANG8,
  PED_TYPE_GANG9,
  PED_TYPE_GANG10,
  PED_TYPE_DEALER,
  PED_TYPE_MEDIC,
  PED_TYPE_FIREMAN,
  PED_TYPE_CRIMINAL,
  PED_TYPE_BUM,
  PED_TYPE_PROSTITUTE,
  PED_TYPE_SPECIAL,
  PED_TYPE_MISSION1,
  PED_TYPE_MISSION2,
  PED_TYPE_MISSION3,
  PED_TYPE_MISSION4,
  PED_TYPE_MISSION5,
  PED_TYPE_MISSION6,
  PED_TYPE_MISSION7,
  PED_TYPE_MISSION8
};

class AnimBlendFrameData {
  public:
  unsigned int m_nFlags;
  CVector m_vecOffset;
  void* m_pIFrame;
  int iNodeId;
};

class CPedAcquaintance {
  public:
  unsigned int m_nRespect;
  unsigned int m_nLike;
  unsigned int m_nIgnore;
  unsigned int m_nDislike;
  unsigned int m_nHate;
};

struct CTaskManager {
  void* m_tasks[5];
  void* m_tasksSecondary[6];
  CPed* m_pPed;
};

struct CMentalState {
  std::uint8_t m_iAngerAtPlayer;
  std::uint8_t m_iLastAngerAtPlayer;
  CTaskTimer m_angerTimer;
  std::uint16_t m_iHealth;
  std::uint16_t m_iLastHealth;
  std::uint16_t m_iCarHealth;
  std::uint16_t m_iLastCarHealth;
  std::uint8_t m_bInCarLastTime;
};

struct CPedStuckChecker {
  enum {
    PED_NOT_STUCK = 0x0,
    PED_STUCK_STAND_FOR_JUMP = 0x1,
    PED_STUCK_JUMP_FALLOFF_SIDE = 0x2,
  };

  CVector m_vecPreviousPos;
  std::uint16_t m_nStuckCounter;
  std::uint16_t m_nStuck;
};

struct CPedIntelligence {
  CPed* m_pPed;
  CTaskManager m_taskManager;
  CEventHandler m_eventHandler;
  CEventGroup m_eventGroup;
  int m_iDecisionMakerType;
  int m_iDecisionMakerTypeInGroup;
  float m_fHearingRange;
  float m_fSeeingRange;
  int m_iMaxNumFriendsToInform;
  float m_fMaxInformFriendDistance;
  float m_fFollowNodeThresholdDistance;
  std::int8_t m_iNextEventResponseSequence;
  std::uint8_t m_iHighestPriorityEventType;
  std::uint8_t m_iHighestPriorityEventPriority;
  CEntityScanner m_vehicleScanner;
  CEntityScanner m_pedScanner;
  CMentalState m_mentalState;
  CEventScanner m_eventScanner;
  CCollisionEventScanner m_collisionEventScanner;
  CPedStuckChecker m_stuckChecker;
  int m_iStaticCounter;
  std::uint32_t m_iNumFramesWithoutCollision;
  CVector m_vPedPositionAtFirstCollision;
  CEntity* m_pInterestingEntities[3];
};