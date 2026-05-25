#pragma once
#include <string>
#include <vector>

namespace compat {
void init();

inline std::string gtasa_name;
inline std::vector<std::string> compat_scripts;
inline std::string profile_name;

inline std::string samp_name;
inline std::string receiveignorerpc_pattern;
inline std::string cnetgame_ctor_pattern;
inline std::uintptr_t rakclientinterface_netgame_offset;
inline bool use_samp_touch_workaround;
inline std::uintptr_t nveventinsertnewest_offset;
}