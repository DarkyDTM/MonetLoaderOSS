#pragma once
#include <cstdint>
struct CEntity;
struct CPed;

struct CTaskTimer {
  int m_iStartTime;
  int m_iDuration;
  std::uint8_t m_bIsActive;
  std::uint8_t m_bIsStopped;
};

struct CEventHandlerHistory {
  void* m_pAbortedTask;
  void* m_pCurrentEventActive;
  void* m_pCurrentEventPassive;
  void* m_pStoredEventActive;
  CTaskTimer m_storeTimer;
};

struct CEventHandler {
  CPed* m_pPed;
  CEventHandlerHistory m_history;
  void* m_pTaskPhysResponse;
  void* m_pTaskEventResponse;
  void* m_pTaskSecondaryAim;
  void* m_pTaskSecondarySay;
  void* m_pTaskSecondaryPartialAnim;
};

struct CEventGroup {
  void** vtbl;
  CPed* m_pPed;
  int m_iNoOfEvents;
  void* m_events[16];
};

struct CGenericScanner {
  CTaskTimer m_timer;
};

struct CAttractorScanner {
  bool m_bActivated;
  CTaskTimer m_timer;
  void* m_pPreviousEffect;
  CEntity* m_pPreviousEntity;
  CEntity* m_entities[10];
  void* m_effects[10];
  float m_minDistanceSquared[10];
};

struct CPedAcquaintanceScanner {
  CTaskTimer m_timer;
  bool m_bActivatedEverywhere;
  bool m_bActivatedInVehicle;
  bool m_bActivatedDuringScriptCommands;
};

struct CCollisionEventScanner
{
  bool m_bAlreadyHitByCar;
};

struct CEventScanner {
  std::int32_t m_startTime;
  CGenericScanner m_vehicleCollisionScanner;
  CGenericScanner m_objectCollisionScanner;
  CAttractorScanner m_attractorScanner;
  CPedAcquaintanceScanner m_acquaintanceScanner;
  CGenericScanner m_sexyPedScanner;
  CGenericScanner m_fireScanner;
};