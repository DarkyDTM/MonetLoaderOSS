#pragma once
#include "OS.h"

namespace game {
struct ButtonStateChange
{
  int buttonIndex;
  OSPointerState state;
  int x;
  int y;
  double timeStamp;
  float force;
};

template<int N>
struct ButtonContainer
{
  OSPointerState curState[N];
  int curX;
  int curY;
  float curForce;
  int systemX;
  int systemY;
  float systemForce;
  OSArray<ButtonStateChange> pendingChanges;
  float doubleClickDelay;
  bool doubleClicked[N];
  double lastUp[N];
  int lastUpX[N];
  int lastUpY[N];
  float AccumulatedWheelDelta;
  float WheelDelta;
};

}