#include <cstdint>

#ifdef __arm__
#include "hook/backend32/inlineHook.h"
#elif defined(__aarch64__)
#include "hook/backend64/And64InlineHook.hpp"
#else
#error "Unknown platform"
#endif

extern "C" __attribute__((visibility("default"))) int monethook_hook_enable(std::uintptr_t address, std::uintptr_t func, std::uintptr_t* orig)
{
#ifdef __arm__
	int status;

	status = registerInlineHook(address, func, reinterpret_cast<uint32_t**>(orig));
	if (status != ELE7EN_OK) {
		return 0x10000 + status;
	}

  status = inlineHook(address);
  if (status != ELE7EN_OK) {
  	return 0x20000 + status;
  }

#elif defined(__aarch64__)
  int status = A64HookFunction(reinterpret_cast<void*>(address), reinterpret_cast<void*>(func), reinterpret_cast<void**>(orig));
  if (status != A64_HOOK_SUCCESS) {
    return 0x10000 + status;
	}
#endif

	return 0;
}

extern "C" __attribute__((visibility("default"))) int monethook_hook_disable(std::uintptr_t address)
{
#ifdef __arm__
  int status = inlineUnHook(address);
  if (status != ELE7EN_OK) {
  	return 0x30000 + status;
  }

#elif defined(__aarch64__)
  int status = A64UnHookFunction(reinterpret_cast<void*>(address));
  if (status != A64_HOOK_SUCCESS) {
    return 0x30000 + status;
  }
#endif

	return 0;
}