#pragma once
#include "CVector2D.h"
#include "OS.h"
#include "lib_manager.h"
#include <cstdint>

struct MobileMenu {
  CVector2D bgUVSize;
  CVector2D bgTargetCoords;
  CVector2D bgCurCoords;
  CVector2D bgStartCoords;
  game::OSArray<void*> screenStack;
  void* pendingScreen;
  void* bgTex;
  void* sliderEmpty;
  void* sliderFull;
  void* sliderNub;
  void* controlsBack;
  void* controlsBack2;
  std::int32_t waypoint_blip;
  char m_WantsToRestartGame; // bool8
  bool WantsToLoad;
  int SelectedSlot;
  bool CurrentGameNotResumable;
  bool InitializedForSignOut;
  float NEW_MAP_SCALE;
  float MAP_OFFSET_X;
  float MAP_OFFSET_Y;
  float MAP_AREA_X;
  float MAP_AREA_Y;
  bool DisplayingMap;
  bool isMapMode;
  bool pointerMode;
  bool isMouse;
  CVector2D pointerCoords[4];
  int pointerState[4];
  unsigned int pointerPress[4];

  static inline MobileMenu* Get()
  {
    return reinterpret_cast<MobileMenu*>(lib_manager::mobile_menu);
  }
};
