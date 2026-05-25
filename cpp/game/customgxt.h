#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include "hook/monethook.h"

namespace customgxt {
void init(monethook::plt_scanner& sc);
std::string find(const char* gxt_key);
void add(std::string gxt_key, const char* ascii);
void remove(std::string gxt_key);
std::string find_free_gxt_key();
}