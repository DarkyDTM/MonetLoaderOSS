#pragma once
#include <cstdint>
#include <string>

namespace lib_manager {
inline std::uintptr_t gtasa_base;
inline std::string gtasa_path;
inline std::uintptr_t samp_base;
inline std::string samp_path;

inline std::uintptr_t samp_receive_ignore;

inline std::uintptr_t got_and_touchevent;

inline std::uintptr_t process_one_command;
inline std::uintptr_t ctouchinterface_istouched;
inline std::uintptr_t ascii_to_gxt_char;
inline std::uintptr_t gxt_char_to_ascii;
inline std::uintptr_t add_big_message;
inline std::uintptr_t add_message;
inline std::uintptr_t add_message_jumpq;
inline std::uintptr_t process_line_of_sight;
inline std::uintptr_t calc_screen_coors;

inline std::uintptr_t set_scissor;
inline std::uintptr_t rw_render_state_get;
inline std::uintptr_t rw_render_state_set;
inline std::uintptr_t rwim2d_render_indexed_primitive;
inline std::uintptr_t rwim2d_get_near_screen_z;
inline std::uintptr_t rw_raster_destroy;
inline std::uintptr_t rw_raster_create;
inline std::uintptr_t rw_raster_set_from_image;
inline std::uintptr_t rw_raster_lock;
inline std::uintptr_t rw_raster_unlock;
inline std::uintptr_t rw_image_create;
inline std::uintptr_t rw_image_allocate_pixels;
inline std::uintptr_t rw_image_find_raster_format;
inline std::uintptr_t rw_image_destroy;
inline std::uintptr_t rt_png_image_read;

inline std::uintptr_t ped_pool;
inline std::uintptr_t vehicle_pool;
inline std::uintptr_t object_pool;
inline std::uintptr_t radar_traces;
inline std::uintptr_t mobile_menu;
inline std::uintptr_t pause_1;
inline std::uintptr_t pause_2;
inline std::uintptr_t rsglobal;
inline std::uintptr_t thetext;
inline std::uintptr_t thecamera;
inline std::uintptr_t recip_near_clip;
inline std::uintptr_t pads;
};