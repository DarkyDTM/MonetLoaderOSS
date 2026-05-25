#ifndef HAS_INCLUDED_LUASEC_API_H
#define HAS_INCLUDED_LUASEC_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "compat.h"

LSEC_API int luaopen_ssl_config(lua_State* L);
LSEC_API int luaopen_ssl_context(lua_State* L);
LSEC_API int luaopen_ssl_core(lua_State* L);
LSEC_API int luaopen_ssl_x509(lua_State *L);

#ifdef __cplusplus
}
#endif

#endif /* HAS_INCLUDED_LUASEC_API_H */