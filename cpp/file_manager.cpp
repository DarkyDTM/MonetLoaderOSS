#include "file_manager.h"
#include "utils/android.h"
#include <filesystem>

void file_manager::init()
{
  external_storage = std::filesystem::path { andutils::jni::get_external_storage() }.parent_path();
  public_external_storage = std::filesystem::path { andutils::jni::get_external_media() };

  // Initialize internal storage path
  internal_storage = "/data/data/" + andutils::get_package_name() + "/";
}