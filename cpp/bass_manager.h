#pragma once
#include "bass.h"
#include <cstdint>

namespace bass_manager {
inline std::uint32_t device;
inline bool inited;

struct context {
  context()
  {
    old_device = BASS_GetDevice();
    BASS_SetDevice(device);
  }

  ~context()
  {
    BASS_SetDevice(old_device);
  }

  private:
  std::uint32_t old_device;
};

void init();
}