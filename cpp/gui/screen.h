#pragma once
#include "imgui/imgui.h"

namespace gui {
namespace screen {
  inline constexpr ImVec2 REFERENCE_SIZE { 2160, 1080 };
  inline ImVec2 size;
  inline ImVec2 scale;
  inline float aspect_ratio;

  inline void update_size(const ImVec2& new_screen_size)
  {
    size = new_screen_size;
    scale = { new_screen_size.x / REFERENCE_SIZE.x, new_screen_size.y / REFERENCE_SIZE.y };
    aspect_ratio = new_screen_size.x / new_screen_size.y;
  }
}

inline float scaled_x(float scalable_x)
{
  return scalable_x * screen::scale.x;
}

inline float scaled_y(float scalable_y)
{
  return scalable_y * screen::scale.y;
}

inline ImVec2 scaled(const ImVec2& scalable_pixels)
{
  return { scalable_pixels.x * screen::scale.x, scalable_pixels.y * screen::scale.y };
}
}