#ifndef SERIAL_H
#define SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "luasocket.h"

LUASOCKET_API int luaopen_socket_serial(lua_State* L);

#ifdef __cplusplus
}
#endif

#endif