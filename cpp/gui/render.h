#pragma once
#include <cstdint>
#include <string_view>

namespace gui::render {
float get_dpi_scale();

void init();
void new_frame();
void end_frame();
void render();
void render_overlay();
void deinit();

void init_keyboard(void* io);
void show_keyboard(void* io, void* style);
void hide_keyboard(void* io);
bool handle_touch(int type, int num, int x, int y);

void draw_line(float x1, float y1, float x2, float y2, float width, std::uint32_t color);
void draw_box(float x, float y, float w, float h, std::uint32_t color);
void draw_box_with_border(float x, float y, float w, float h, std::uint32_t color, float bsize, std::uint32_t bcolor);
void draw_polygon(float x, float y, float w, float h, int corners, float rotation, std::uint32_t color);
void draw_image(void* texture, float x, float y, float w, float h, float rotation, std::uint32_t color);

std::int32_t get_font(int size, bool outline);
float get_text_length(std::int32_t handle, std::string_view text, bool ignore_color_tags = false);
int get_font_height(std::int32_t handle);
void draw_font(std::int32_t handle, std::string_view text, float x, float y, std::uint32_t color, bool ignore_color_tags = false);
}