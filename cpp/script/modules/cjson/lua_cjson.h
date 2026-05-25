#ifndef HAS_INCLUDED_CJSON_LUA_CJSON_H
#define HAS_INCLUDED_CJSON_LUA_CJSON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lua.h>

int luaopen_cjson(lua_State *l);
int luaopen_cjson_safe(lua_State *l);

#ifdef __cplusplus
}
#endif

#endif /* HAS_INCLUDED_CJSON_LUA_CJSON_H */