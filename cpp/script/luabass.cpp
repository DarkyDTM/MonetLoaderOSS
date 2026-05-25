#include "luabass.h"
#include "bass.h"
#include "bass_manager.h"
#include "game/audiostream.h"
#include "game/audiostream_sync.h"
#include "sol/sol.hpp"

namespace {
struct audiostream_wrapper {
  audiostream_wrapper(HSTREAM stream) noexcept
      : stream { stream }
  {
  }

  ~audiostream_wrapper()
  {
    if (stream != 0) {
      game::audiostream_sync::remove(stream);
      game::audiostream::release(stream);
    }
  }

  audiostream_wrapper(audiostream_wrapper&& from) noexcept
      : stream { from.stream }
  {
    from.stream = 0;
  }

  audiostream_wrapper& operator=(audiostream_wrapper&& from) noexcept
  {
    std::swap(stream, from.stream);
    return *this;
  }

  // Copying not allowed.
  audiostream_wrapper(const audiostream_wrapper&) = delete;
  audiostream_wrapper& operator=(const audiostream_wrapper&) = delete;

  HSTREAM stream;
};
}

void luabass::reg(sol::state& state)
{
  state.new_usertype<audiostream_wrapper>("AudioStream", sol::no_constructor);

  state["monet_is_audiostream_available"] = []() {
    return bass_manager::inited;
  };

  state["monet_get_audiostream_handle"] = [](const audiostream_wrapper& handle) {
    return handle.stream;
  };

  state["loadAudioStream"] = [](const char* path) {
    return audiostream_wrapper { game::audiostream::create(path, false) };
  };
  state["load3dAudioStream"] = [](const char* path) {
    return audiostream_wrapper { game::audiostream::create(path, true) };
  };
  state["loadAudioStreamFromMemory"] = [](std::uintptr_t address, std::size_t size) {
    return audiostream_wrapper { game::audiostream::create(reinterpret_cast<void*>(address), size, false) };
  };
  state["load3dAudioStreamFromMemory"] = [](std::uintptr_t address, std::size_t size) {
    return audiostream_wrapper { game::audiostream::create(reinterpret_cast<void*>(address), size, true) };
  };
  state["releaseAudioStream"] = [](audiostream_wrapper& handle) {
    game::audiostream_sync::remove(handle.stream);
    game::audiostream::release(handle.stream);
    handle.stream = 0;
  };

  state["getAudioStreamLength"] = [](const audiostream_wrapper& handle) {
    return game::audiostream::get_length(handle.stream);
  };
  state["getAudioStreamState"] = [](const audiostream_wrapper& handle) {
    return static_cast<int>(game::audiostream::get_state(handle.stream));
  };
  state["getAudioStreamVolume"] = [](const audiostream_wrapper& handle) {
    return game::audiostream::get_volume(handle.stream);
  };
  state["getAudioStreamLooped"] = [](const audiostream_wrapper& handle) {
    return game::audiostream::get_looped(handle.stream);
  };

  state["setAudioStreamPosition"] = [](const audiostream_wrapper& handle, double pos) {
    return game::audiostream::set_pos(handle.stream, pos);
  };
  state["setAudioStreamState"] = [](const audiostream_wrapper& handle, int state) {
    return game::audiostream::set_state(handle.stream, static_cast<game::audiostream::state>(state));
  };
  state["setAudioStreamVolume"] = [](const audiostream_wrapper& handle, float volume) {
    return game::audiostream::set_volume(handle.stream, volume);
  };
  state["setAudioStreamLooped"] = [](const audiostream_wrapper& handle, bool looped) {
    return game::audiostream::set_looped(handle.stream, looped);
  };

  state["setPlay3dAudioStreamAtCoordinates"] = [](const audiostream_wrapper& handle, float x, float y, float z) {
    return game::audiostream_sync::add(handle.stream, game::audiostream_sync::type::COORDS, 0, CVector { x, y, z });
  };
  state["setPlay3dAudioStreamAtObject"] = [](const audiostream_wrapper& handle, int object) {
    return game::audiostream_sync::add(handle.stream, game::audiostream_sync::type::OBJECT, object);
  };
  state["setPlay3dAudioStreamAtChar"] = [](const audiostream_wrapper& handle, int ped) {
    return game::audiostream_sync::add(handle.stream, game::audiostream_sync::type::CHAR, ped);
  };
  state["setPlay3dAudioStreamAtCar"] = [](const audiostream_wrapper& handle, int car) {
    return game::audiostream_sync::add(handle.stream, game::audiostream_sync::type::CAR, car);
  };
}