#pragma once
#include "imgui/imgui.h"

namespace imrw {
// ImGui stuff
void init();
void render_draw_data(ImDrawData* draw_data);
void create_font();
void destroy_font();
void shutdown();
void new_frame();

// Image stuff
struct image_data {
  ImTextureID raster;
  float width;
  float height;
};

image_data load_image(const char* path);
image_data load_image_from_memory(const unsigned char* data, int length);
image_data get_image_data(ImTextureID raster);
void destroy_image(ImTextureID raster);
}