#pragma once
#include <cstddef>
#include <cstdint>
#include <optional>
#include <sol/sol.hpp>

namespace lua::memory {
void write(std::uintptr_t address, std::size_t size, std::int32_t value, std::optional<bool> unprotect);
std::int32_t read(std::uintptr_t address, std::size_t size, std::optional<bool> unprotect);
void write64(std::uintptr_t address, double value, bool unsign, std::optional<bool> unprotect);
double read64(std::uintptr_t address, bool unsign, std::optional<bool> unprotect);
void unprotect(std::uintptr_t address, std::size_t size);
void copy(std::uintptr_t dst, std::uintptr_t src, std::size_t size, std::optional<bool> unprotect);
bool compare(std::uintptr_t a, std::uintptr_t b, std::size_t size);
void fill(std::uintptr_t address, int value, std::size_t size, std::optional<bool> unprotect);
void write_hex(const char* hex, std::uintptr_t address, std::size_t size, std::optional<bool> unprotect);
std::string hex_to_data(const std::string& hex);

sol::table reg(sol::this_state state);
}