#pragma once
#include <sol/sol.hpp>

namespace lua::mimgui {
sol::table reg_renderer(sol::this_state state);
bool handle_touch(int type, int num, int x, int y);
void render();
}