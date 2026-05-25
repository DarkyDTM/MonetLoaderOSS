#pragma once
#include <filesystem>
#include <string>

namespace file_manager {
void init();
inline std::filesystem::path external_storage;
inline std::filesystem::path public_external_storage;
inline std::filesystem::path internal_storage;
};