target_sources(${PROJECT_NAME} PRIVATE
    cpp/hook/backend32/inlineHook.c
    cpp/hook/backend32/relocate.c
    cpp/hook/backend64/And64InlineHook.cpp
    cpp/hook/monethook.cpp

    cpp/utils/random.cpp
    cpp/utils/str.cpp
    cpp/utils/android.cpp

    cpp/game/customgxt.cpp
    cpp/game/netinfo.cpp
    cpp/game/rakhook.cpp
    cpp/game/ScriptCommands.cpp

    cpp/gui/imrw.cpp
    cpp/gui/render.cpp
    cpp/gui/touch_handler.cpp
    cpp/gui/input_system.cpp
    cpp/gui/keyboard.cpp

    cpp/script/modules/mimgui/renderer.cpp
    cpp/script/modules/mimgui/cimgui.cpp

    cpp/script/modules/effil/channel.cpp
    cpp/script/modules/effil/function.cpp
    cpp/script/modules/effil/garbage-collector.cpp
    cpp/script/modules/effil/gc-data.cpp
    cpp/script/modules/effil/logger.cpp
    cpp/script/modules/effil/lua-helpers.cpp
    cpp/script/modules/effil/lua-module.cpp
    cpp/script/modules/effil/shared-table.cpp
    cpp/script/modules/effil/stored-object.cpp
    cpp/script/modules/effil/this-thread.cpp
    cpp/script/modules/effil/thread-handle.cpp
    cpp/script/modules/effil/thread-runner.cpp
    cpp/script/modules/effil/thread.cpp

    cpp/script/modules/luasocket/auxiliar.c
    cpp/script/modules/luasocket/buffer.c
    cpp/script/modules/luasocket/compat.c
    cpp/script/modules/luasocket/except.c
    cpp/script/modules/luasocket/inet.c
    cpp/script/modules/luasocket/io.c
    cpp/script/modules/luasocket/luasocket.c
    cpp/script/modules/luasocket/mime.c
    cpp/script/modules/luasocket/options.c
    cpp/script/modules/luasocket/select.c
    cpp/script/modules/luasocket/serial.c
    cpp/script/modules/luasocket/tcp.c
    cpp/script/modules/luasocket/timeout.c
    cpp/script/modules/luasocket/udp.c
    cpp/script/modules/luasocket/unix.c
    cpp/script/modules/luasocket/unixdgram.c
    cpp/script/modules/luasocket/unixstream.c
    cpp/script/modules/luasocket/usocket.c
    cpp/script/modules/luasocket/wsocket.c
    
    cpp/script/modules/luasec/config.c
    cpp/script/modules/luasec/context.c
    cpp/script/modules/luasec/ec.c
    cpp/script/modules/luasec/options.c
    cpp/script/modules/luasec/ssl.c
    cpp/script/modules/luasec/x509.c

    # cpp/script/modules/cjson/dtoa.c
    cpp/script/modules/cjson/fpconv.c
    # cpp/script/modules/cjson/g_fmt.c
    cpp/script/modules/cjson/lua_cjson.c
    cpp/script/modules/cjson/strbuf.c

    cpp/script/modules/lfs.c
    cpp/script/modules/lbase64.c
    cpp/script/modules/monethook.cpp
    cpp/script/modules/memory.cpp

    cpp/script/luabass.cpp
    cpp/script/luajson.cpp
    cpp/script/luafuncs.cpp
    cpp/script/opcodes.cpp
    cpp/script/scheduler.cpp
    cpp/script/script_manager.cpp
    cpp/script/script.cpp
    cpp/script/thread.cpp

    cpp/clipboard.cpp
    cpp/file_manager.cpp
    cpp/bass_manager.cpp
    cpp/logger.cpp
    cpp/compat.cpp
    cpp/main.cpp
    )