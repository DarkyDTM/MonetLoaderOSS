#pragma once
#include "CEntity.h"
#include "CObject.h"
#include "raknet/BitStream.h"
#include "sync.h"
#include <chrono>
#include <cstdint>
#include <string>
#include <array>
#include <unordered_map>

struct CPed;
struct CVehicle;

namespace game {
class netinfo {
  public:
  struct player {
    std::uint16_t id;
    std::string name;
    bool npc;
    std::uint32_t color;
    std::int32_t score;
    std::int32_t ping;

    bool streamed_in; // spawned in local player
    std::uint8_t reported_health;
    std::uint8_t reported_armor;

    std::chrono::steady_clock::time_point last_recv;
    sync::onfoot last_onfoot_sync;
    sync::vehicle last_vehicle_sync;
    sync::passenger last_passenger_sync;
    sync::trailer last_trailer_sync;
    sync::aim last_aim_sync;
  };

  struct text_3d {
    bool active;
    std::string text;
    std::uint32_t color;
    float x, y, z;
    float distance;
    bool ignore_walls;
    std::uint16_t playerid;
    std::uint16_t vehicleid;
  };

  struct dialog_info {
    bool shown;
    bool clientside;
    bool pending_emulation;
    bool respond;
    std::int16_t id;
    std::uint8_t type;
    std::string caption;
    std::string text;

    int last_button;
    int last_list;
    std::string last_input;
  };

  static void add(CEntity* ptr)
  {
    if (_current_entity_type == entity_t::ped && ptr->m_nType == ENTITY_TYPE_PED && !_current_expected_remove) {
      if (_current_ped_step != 0 && _current_ped_step != 2) {
        _current_entity_type = entity_t::none;
        return;
      }

      if (_current_ped_step == 2) {
        player_stream_in(_current_entity_id, reinterpret_cast<CPed*>(ptr));
        _current_entity_type = entity_t::none;
        return;
      }

      ++_current_ped_step;
      return;
    }
    if (_current_entity_type == entity_t::vehicle && ptr->m_nType == ENTITY_TYPE_VEHICLE && !_current_expected_remove) {
      car_stream_in(_current_entity_id, reinterpret_cast<CVehicle*>(ptr));
      _current_entity_type = entity_t::none;
      return;
    }
    if (_current_entity_type == entity_t::object && ptr->m_nType == ENTITY_TYPE_OBJECT && !_current_expected_remove) {
      object_stream_in(_current_entity_id, reinterpret_cast<CObject*>(ptr));
      _current_entity_type = entity_t::none;
      return;
    }
  }

  static void remove(CEntity* ptr)
  {
    if (_current_entity_type == entity_t::ped && ptr->m_nType == ENTITY_TYPE_PED) {
      if (!_current_expected_remove && _current_ped_step != 1) {
        _current_entity_type = entity_t::none;
        return;
      }

      if (_current_expected_remove) {
        player_stream_out(_current_entity_id);
        _current_entity_type = entity_t::none;
        return;
      }

      ++_current_ped_step;
      return;
    }
    if (_current_entity_type == entity_t::vehicle && ptr->m_nType == ENTITY_TYPE_VEHICLE && _current_expected_remove) {
      car_stream_out(_current_entity_id);
      _current_entity_type = entity_t::none;
      return;
    }
    if (_current_entity_type == entity_t::object && ptr->m_nType == ENTITY_TYPE_OBJECT && _current_expected_remove) {
      object_stream_out(_current_entity_id);
      _current_entity_type = entity_t::none;
      return;
    }
  }

  static void reset_add_remove()
  {
    _current_entity_type = entity_t::none;
  }

  static CPed* find_ped(std::uint16_t id)
  {
    auto it = _id_to_ped.find(id);
    if (it == _id_to_ped.end()) {
      return nullptr;
    }

    return it->second;
  }
  static CVehicle* find_car(std::uint16_t id)
  {
    auto it = _id_to_car.find(id);
    if (it == _id_to_car.end()) {
      return nullptr;
    }

    return it->second;
  }
  static CObject* find_object(std::uint16_t id)
  {
    auto it = _id_to_object.find(id);
    if (it == _id_to_object.end()) {
      return nullptr;
    }

    return it->second;
  }

  static std::uint16_t find_ped_id(CPed* ped)
  {
    auto it = _ped_to_id.find(ped);
    if (it == _ped_to_id.end()) {
      return -1;
    }

    return it->second;
  }
  static std::uint16_t find_car_id(CVehicle* car)
  {
    auto it = _car_to_id.find(car);
    if (it == _car_to_id.end()) {
      return -1;
    }

    return it->second;
  }
  static std::uint16_t find_object_id(CObject* object)
  {
    auto it = _object_to_id.find(object);
    if (it == _object_to_id.end()) {
      return -1;
    }

    return it->second;
  }

  static std::uint16_t find_max_streamed_ped_id()
  {
    std::uint16_t id = -1;
    for (auto i : _ped_to_id) {
      if (id == static_cast<std::uint16_t>(-1) || i.second > id) {
        id = i.second;
      }
    }

    return id;
  }

  static std::uint16_t find_streamed_ped_count()
  {
    return _ped_to_id.size();
  }

  static std::uint16_t find_streamed_car_count()
  {
    return _car_to_id.size();
  }

  static void process();
  static void handle_outcoming_packet(std::uint8_t id, RakNet::BitStream* bs);
  static bool handle_outcoming_rpc(std::uint8_t id, RakNet::BitStream* bs);
  static void handle_incoming_packet(std::uint8_t id, RakNet::BitStream* bs);
  static bool handle_incoming_rpc(std::uint8_t id, RakNet::BitStream* bs);

  static inline std::uint16_t max_id;
  static inline std::uint16_t online { 1 };
  static inline std::uint16_t local_player_id;
  static inline player local_player {};
  static inline std::unordered_map<std::uint16_t, player> remote_players;
  static inline std::array<text_3d, 2048> texts_3d;
  static inline dialog_info dialog {};
  static inline std::string hostname { "SA-MP" };
  static inline std::string address {};
  static inline std::uint16_t port {};

  private:
  static void reset()
  {
    local_player.streamed_in = false;
    max_id = local_player_id;
    online = 1;
    remote_players.clear();
    _ped_to_id.clear();
    _car_to_id.clear();
    _object_to_id.clear();
    _id_to_ped.clear();
    _id_to_car.clear();
    _id_to_object.clear();
  }

  static void player_stream_in(std::uint16_t id, CPed* ped)
  {
    remote_players[id].streamed_in = true;
    _ped_to_id[ped] = id;
    _id_to_ped[id] = ped;
  }
  static void player_stream_out(std::uint16_t id)
  {
    remote_players[id].streamed_in = false;
    _ped_to_id.erase(_id_to_ped[id]);
    _id_to_ped.erase(id);
  }

  static void car_stream_in(std::uint16_t id, CVehicle* car)
  {
    _car_to_id[car] = id;
    _id_to_car[id] = car;
  }
  static void car_stream_out(std::uint16_t id)
  {
    _car_to_id.erase(_id_to_car[id]);
    _id_to_car.erase(id);
  }

  static void object_stream_in(std::uint16_t id, CObject* object)
  {
    _object_to_id[object] = id;
    _id_to_object[id] = object;
  }
  static void object_stream_out(std::uint16_t id)
  {
    _object_to_id.erase(_id_to_object[id]);
    _id_to_object.erase(id);
  }

  static inline bool _requested_tab;
  static inline std::chrono::steady_clock::time_point _last_tab_update;

  enum class entity_t {
    none,
    ped,
    vehicle,
    object
  };
  static inline entity_t _current_entity_type;
  static inline std::uint16_t _current_entity_id;
  static inline bool _current_expected_remove;
  static inline int _current_ped_step;

  static inline std::unordered_map<CPed*, std::uint16_t> _ped_to_id;
  static inline std::unordered_map<CVehicle*, std::uint16_t> _car_to_id;
  static inline std::unordered_map<CObject*, std::uint16_t> _object_to_id;
  static inline std::unordered_map<std::uint16_t, CPed*> _id_to_ped;
  static inline std::unordered_map<std::uint16_t, CVehicle*> _id_to_car;
  static inline std::unordered_map<std::uint16_t, CObject*> _id_to_object;
};
};