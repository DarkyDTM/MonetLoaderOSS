#pragma once
#include <sol/sol.hpp>

namespace opcodes {
int getPlayerChar(int self);
float getGroundZFor3dCoord(float x, float y, float z);

void reg(sol::state& s);
}