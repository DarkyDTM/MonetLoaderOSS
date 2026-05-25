#include "clipboard.h"
#include "utils/android.h"

namespace {
thread_local static JNIEnv* g_env = nullptr;
}

std::string clipboard::get()
{
  if (!g_env) {
    andutils::java_getter env {};
    env.retain();
    g_env = env.env();
  }

  return andutils::jni::get_clipboard(g_env);
}

void clipboard::set(const char* value)
{
  if (!g_env) {
    andutils::java_getter env {};
    env.retain();
    g_env = env.env();
  }

  return andutils::jni::set_clipboard(g_env, value);
}