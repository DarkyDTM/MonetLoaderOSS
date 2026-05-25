#include "renderer.h"
#include "gui/imrw.h"
#include "gui/input_system.h"
#include "gui/render.h"
#include "gui/touch_handler.h"
#include "imgui/imgui.h"
#include <list>
#include <ranges>

namespace {
struct imgui_renderer;
std::list<imgui_renderer*> g_all_renderers;

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

struct imgui_renderer {
  imgui_renderer()
  {
    ImGui::SetCurrentContext(nullptr);
    ctx = ImGui::CreateContext();
    if (!ctx) {
      throw sol::error { "failed to create context!" };
    }
    ImGui::SetCurrentContext(ctx);
    imrw::init();
    ImGui::StyleColorsDark();
    gui::render::init_keyboard(&ImGui::GetIO());

    handler.init(&ImGui::GetIO(), ImGui::GetCurrentContext());
    g_all_renderers.push_front(this);
    all_renderers_iterator = g_all_renderers.begin();
  }

  ~imgui_renderer()
  {
    ImGui::SetCurrentContext(ctx);
    gui::render::hide_keyboard(&ImGui::GetIO());
    imrw::shutdown();
    ImGui::DestroyContext(ctx);
    input_system::destroyed_context();

    g_all_renderers.erase(all_renderers_iterator);
  }

  void switch_context()
  {
    ImGui::SetCurrentContext(ctx);
  }

  void destroy_font()
  {
    imrw::destroy_font();
  }
  void create_font()
  {
    imrw::create_font();
  }

  void begin_frame()
  {
    ImGui::SetCurrentContext(ctx);
    imrw::new_frame();
    ImGui::NewFrame();
  }

  void end_frame()
  {
    input_system::end_frame();
    ImGui::EndFrame();
    handler.end_frame();
    ImGui::Render();
    has_frame = true;

    if (ImGui::GetIO().WantTextInput && enabled_io) {
      gui::render::show_keyboard(&ImGui::GetIO(), &ImGui::GetStyle());
    } else {
      gui::render::hide_keyboard(&ImGui::GetIO());
    }
  }

  void render()
  {
    if (!has_frame)
      return;
    ImGui::SetCurrentContext(ctx);
    imrw::render_draw_data(ImGui::GetDrawData());
    has_frame = false;
  }

  void enable_io(bool enable)
  {
    imgui_context_switch sw { ctx };

    if (!enable) {
      ImGuiIO& io = ImGui::GetIO();
      if (ImGui::IsMouseDown(0)) {
        io.MouseDown[0] = false;
        io.MousePos = { -FLT_MAX, -FLT_MAX };
      }
    }
    enabled_io = enable;
    handler.enable_touches(enable);
  }

  ImTextureID create_texture_from_file(const char* file)
  {
    return imrw::load_image(file).raster;
  }

  ImTextureID create_texture_from_file_in_memory(std::uintptr_t ptr, int size)
  {
    return imrw::load_image_from_memory(reinterpret_cast<unsigned char*>(ptr), size).raster;
  }

  void release_texture(std::uintptr_t ptr)
  {
    return imrw::destroy_image(reinterpret_cast<ImTextureID>(ptr));
  }

  bool handle_touch(const touch_handler::touch_data& data)
  {
    return handler.handle(data);
  }

  private:
  ImGuiContext* ctx;
  touch_handler handler {};
  int active_touch_id { -1 };
  std::list<imgui_renderer*>::iterator all_renderers_iterator;
  bool has_frame { false };
  bool enabled_io { false };
};
}

sol::table lua::mimgui::reg_renderer(sol::this_state this_state)
{
  sol::state_view state = this_state;
  sol::table module = state.create_table();

  module.new_usertype<imgui_renderer>(
      "ImGuiRenderer",
      sol::call_constructor, sol::constructors<imgui_renderer()>(),
      "SwitchContext", &imgui_renderer::switch_context,
      "InvalidateFontsTexture", &imgui_renderer::destroy_font,
      "CreateFontsTexture", &imgui_renderer::create_font,
      "NewFrame", &imgui_renderer::begin_frame,
      "EndFrame", &imgui_renderer::end_frame,
      "EnableIO", &imgui_renderer::enable_io,
      "CreateTextureFromFile", &imgui_renderer::create_texture_from_file,
      "CreateTextureFromFileInMemory", &imgui_renderer::create_texture_from_file_in_memory,
      "ReleaseTexture", &imgui_renderer::release_texture);

  return module;
}

bool lua::mimgui::handle_touch(int type, int num, int x, int y)
{
  touch_handler::touch_data data;
  data.type = static_cast<touch_handler::touch_type>(type);
  data.num = num;
  data.x = x;
  data.y = y;

  for (auto& i : g_all_renderers) {
    if (i->handle_touch(data)) {
      return true;
    }
  }

  return false;
}

void lua::mimgui::render()
{
  for (auto& i : std::ranges::reverse_view(g_all_renderers)) {
    i->render();
  }
}