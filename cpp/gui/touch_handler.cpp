#include "touch_handler.h"
#include "imgui/imgui.h"

void touch_handler::end_frame()
{
  if (need_clear_mouse_pos) {
    io->MousePos = { -FLT_MAX, -FLT_MAX };
    need_clear_mouse_pos = false;
  }

  if (need_clear_mouse_down) {
    io->MouseDown[0] = false;
    need_clear_mouse_down = false;
  }

  if (delayed_push) {
    io->MouseDown[0] = true;
    io->MousePosPrev = io->MousePos = delayed_push_pos; // < ensure imgui doesn't think that we moved
    delayed_push = false;
  }
}