#pragma once
#include "raknet/BitStream.h"
#include "raknet/RakNetTypes.h"
#include "utils/callback.h"
#include <cstdint>
class RakClientInterface;

namespace rakhook {
void init(RakClientInterface* rci, std::uintptr_t recv_ignore_rpc);
bool available();
void process();

namespace emu {
  void clear();
  void only(bool toggle);
  void packet(RakNet::BitStream* bs);
  void rpc(std::uint8_t id, RakNet::BitStream* bs = nullptr);
}

namespace send {
  void packet(RakNet::BitStream* bs, RakNet::PacketPriority priority = RakNet::HIGH_PRIORITY,
      RakNet::PacketReliability reliability = RakNet::UNRELIABLE_SEQUENCED, char ordering_channel = 0);
  void packet_invoke_handlers(RakNet::BitStream* bs, RakNet::PacketPriority priority = RakNet::HIGH_PRIORITY,
      RakNet::PacketReliability reliability = RakNet::UNRELIABLE_SEQUENCED, char ordering_channel = 0);
  void rpc(int id, RakNet::BitStream* bs = nullptr, RakNet::PacketPriority priority = RakNet::HIGH_PRIORITY,
      RakNet::PacketReliability reliability = RakNet::RELIABLE_ORDERED, char ordering_channel = 0);
  void rpc_invoke_handlers(int id, RakNet::BitStream* bs = nullptr, RakNet::PacketPriority priority = RakNet::HIGH_PRIORITY,
      RakNet::PacketReliability reliability = RakNet::RELIABLE_ORDERED, char ordering_channel = 0);
}
};