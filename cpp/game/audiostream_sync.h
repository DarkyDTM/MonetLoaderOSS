#pragma once
#include "CVector.h"
#include "bass.h"
#include "bass_manager.h"
#include "game/CCamera.h"
#include "game/CPools.h"
#include <unordered_map>

namespace game {
struct audiostream_sync {
  enum class type {
    COORDS,
    OBJECT,
    CHAR,
    CAR
  };

  static void add(HSTREAM stream, type t, int handle = 0, CVector pos = {})
  {
    if (!bass_manager::inited) {
      return;
    }

    _streams.erase(stream);
    _streams.emplace(stream, sync_data { t, handle, pos });
  }

  static void remove(HSTREAM stream)
  {
    if (!bass_manager::inited) {
      return;
    }
    _streams.erase(stream);
  }

  static void process()
  {
    if (!bass_manager::inited) {
      return;
    }
    bass_manager::context ctx {};

    // make sure to inverse calculation to ensure correct stereo
    CVector cam_pos = CCamera::GetCamera()->m_cameraMatrix.pos;

    for (auto it = _streams.begin(); it != _streams.end();) {
      if (!BASS_ChannelIsActive(it->first) && BASS_ErrorGetCode() != BASS_OK) {
        it = _streams.erase(it);
        continue;
      }

      switch (it->second.t) {
      case type::COORDS: {
        CVector delta = cam_pos - it->second.pos;
        BASS_3DVECTOR bass_vec { delta.x, delta.y, delta.z };
        BASS_ChannelSet3DPosition(it->first, &bass_vec, nullptr, nullptr);
        break;
      }

      case type::OBJECT: {
        CObject* obj = CPools::GetObjectPool()->GetAtRef(it->second.handle);
        if (!obj) {
          BASS_ChannelStop(it->first);
          it = _streams.erase(it);
          continue;
        }

        CVector delta = cam_pos - obj->GetPosition();
        BASS_3DVECTOR bass_vec { delta.x, delta.y, delta.z };
        BASS_ChannelSet3DPosition(it->first, &bass_vec, nullptr, nullptr);
        break;
      }

      case type::CHAR: {
        CPed* ped = CPools::GetPedPool()->GetAtRef(it->second.handle);
        if (!ped) {
          BASS_ChannelStop(it->first);
          it = _streams.erase(it);
          continue;
        }

        CVector delta = cam_pos - ped->GetPosition();
        BASS_3DVECTOR bass_vec { delta.x, delta.y, delta.z };
        BASS_ChannelSet3DPosition(it->first, &bass_vec, nullptr, nullptr);
        break;
      }

      case type::CAR: {
        CVehicle* car = CPools::GetVehiclePool()->GetAtRef(it->second.handle);
        if (!car) {
          BASS_ChannelStop(it->first);
          it = _streams.erase(it);
          continue;
        }

        CVector delta = cam_pos - car->GetPosition();
        BASS_3DVECTOR bass_vec { delta.x, delta.y, delta.z };
        BASS_ChannelSet3DPosition(it->first, &bass_vec, nullptr, nullptr);
        break;
      }
      }

      ++it;
    }

    BASS_Apply3D();
  }

  private:
  struct sync_data {
    type t;
    int handle;
    CVector pos;
  };

  inline static std::unordered_map<HSTREAM, sync_data> _streams;
};
}