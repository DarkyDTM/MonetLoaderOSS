#include "lib_manager.h"

#ifdef HAS_INCLUDED_GTA_STRUCT_INL
#undef HAS_INCLUDED_GTA_STRUCT_INL
#undef GTA_FUNC_AT
#undef GTA_FUNC_AT_THIS
#undef GTA_FUNC_VTBL_THIS
#else
#define GTA_FUNC_AT(type, addr) (reinterpret_cast<decltype(&type)>(addr))
#define GTA_FUNC_AT_THIS(ret, addr, ...) (reinterpret_cast<ret (*)(decltype(this), ##__VA_ARGS__)>(addr))
#define GTA_FUNC_VTBL_THIS(ret, vtbl, n, ...) (reinterpret_cast<ret (*)(decltype(this), ##__VA_ARGS__)>(vtbl[(n)]))
#define HAS_INCLUDED_GTA_STRUCT_INL
#endif