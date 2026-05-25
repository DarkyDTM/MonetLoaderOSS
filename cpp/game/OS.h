#pragma once

namespace game {
template <typename T>
struct OSArray {
  int numAlloced;
  int numEntries;
  T* dataPtr;
};

enum OSPointerState {
  OSPS_ButtonReleased = 0,
  OSPS_ButtonUp = 1,
  OSPS_ButtonPressed = 2,
  OSPS_ButtonDown = 3,
  OSPS_ButtonInvalid = -1
};
}