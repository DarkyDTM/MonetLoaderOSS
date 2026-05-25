#pragma once
#include "imgui/imgui.h"

struct imgui_context_switch {
  imgui_context_switch(ImGuiContext* ctx)
  {
    _old_ctx = ImGui::GetCurrentContext();
    ImGui::SetCurrentContext(ctx);
  }

  ~imgui_context_switch()
  {
    ImGui::SetCurrentContext(_old_ctx);
  }

  private:
  ImGuiContext* _old_ctx;
};