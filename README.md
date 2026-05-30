[English](/README.md)
[Русский](/README-ru.md)

# MonetLoader 3.8.0
A Lua script loader for GTA: San Andreas (and SAMP) on Android.<br>
Main goal - compatibility with PC MoonLoader (as far as Mobile allows it).

## Source layout:
1. `cpp` - Main MonetLoader code.
   * `game` - GTA and SAMP stuff.
   * `gui` - ImGui, input and script rendering framework.
   * `hook` - MonetHook hooking library.
   * `script` - Main script runtime implementation, `script/modules` contains packaged into MonetLoader modules.
   * `utils` - Various utility.
2. `dist` - Lua redistributable libraries.
3. `example` - Example MonetLoader scripts.
4. `lib` - Third-party code.

## Installation:
1. Setup NDK environment (toolchain, ANDROID_ABI, ANDROID_PLATFORM, ANDROID_STL).
2. Load the root CMakeLists.txt, wait for it to configure and build.
3. Ship generated libmonetloader.so together with respective Lua binary from lib/lua/bin.
4. Copy data from `dist` and scripts into `Android/media/<package name>` at external storage.
