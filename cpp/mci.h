/* monetloader compatibility interface public header */
#ifndef MONETLOADER_MCI_H
#define MONETLOADER_MCI_H

#include <stdint.h>
#include <stddef.h>

// #define MONETLOADER
#define MCI_EXTERN_API extern "C"
#define MCI_API extern "C" __attribute__((visibility("default")))

typedef struct CPed CPed;
typedef struct CVehicle CVehicle;
typedef struct CObject CObject;

// Assumed layout:
// #define BITSTREAM_NATIVE_END
// class BitStream:
// ...
//  int numberOfBitsUsed;
//  int numberOfBitsAllocated;
//  int readOffset;
//  unsigned char *data;
//  bool copyData;
//  unsigned char stackData[256];
typedef struct BitStream BitStream;

typedef struct MCI_INIT_STRUCT
{
  // sizeof(MCI_INIT_STRUCT)
  size_t SizeOfStruct;
  // from profile
  const char* InitData;
  // XYYYZZZ, X - major, Y - minor, Z - patch
  uint32_t Version;

  // Callbacks for RakHook

  // this callback should be called on ANY receive (packet/rpc)
  // returns new packet handle (from CreatePacket in MCI_INTERFACE)
  // and frees old packet handle if it was modified, returns old packet
  // handle if it was not modified (or modified but not changed size)
  // can return nullptr (also frees packet in that case) TO SKIP sending
  // packet to user
  void*(*OnReceiveIgnoreRPC)(void* packetHandle, unsigned char* data, size_t lengthInBytes);
  // this callback should be called on ANY send of RPC
  // it can modify rpc_id, bs, priority, reliability, orderingChannel
  // orderingChannel is not a string (only a char pointer)
  // note that rpc_id is not the same as uniqueID in RakNet!
  // rather you should do:
  // int rpc_id = *uniqueID;
  // if(!OnSendRPC(&rpc_id, ...)) return;
  // rakPeer->RPC(..., &rpc_id, ...);
  // returns true if RPC should be sent, false otherwise (NOPed)
  bool(*OnSendRPC)(int* rpc_id, BitStream* bs, int* priority, int* reliability, char* orderingChannel);
  // this callback should be called on ANY send of packet
  // it can modify bs, priority, reliability, orderingChannel
  // orderingChannel is not a string (only a char pointer)
  // returns true if packet  should be sent, false otherwise (NOPed)
  bool(*OnSendPacket)(BitStream* bs, int* priority, int* reliability, char* orderingChannel);

} MCI_INIT_STRUCT;

typedef struct MCI_INTERFACE
{
  // send specified RPC, it should not call RakHook callbacks
  void(*SendRPC)(int rpc_id, BitStream* bs, int* priority, int* reliability, char* orderingChannel);
  // send specified packet, it should not call RakHook callbacks
  void(*SendPacket)(BitStream* bs, int* priority, int* reliability, char* orderingChannel);

  // allocate a new RakNet::Packet
  // this usually should do something like this (albeit without BitStream):
  // RakNet::Packet* CreateRakNetPacket(RakNet::BitStream* bs)
  // {
  //    auto* pkt = static_cast<RakNet::Packet*>(std::malloc(sizeof(RakNet::Packet)));
  //    pkt->data = new char[bs->GetNumberOfBytesUsed()];
  //    memcpy(pkt->data, bs->GetData(), bs->GetNumberOfBytesUsed());
  //    pkt->length = bs->GetNumberOfBytesUsed();
  //    pkt->playerId = RakNet::UNASSIGNED_PLAYER_ID;
  //    pkt->playerIndex = RakNet::UNASSIGNED_PLAYER_INDEX;
  //    pkt->bitSize = bs->GetNumberOfBitsUsed();
  //    pkt->deleteData = true;
  //    return pkt;
  // }
  void* (*AllocatePacket)(unsigned char* data, size_t lengthInBytes);
  // free specified RakNet::Packet
  // this usually should do something like this:
  // void FreeRakNetPacket(RakNet::Packet* pkt)
  // {
  //    if (pkt->deleteData) {
  //      delete[] pkt->data;
  //    }
  //    free(pkt);
  // }
  void (*FreePacket)(void* packetHandle);
} MCI_INTERFACE;

#ifndef MONETLOADER
// called by monetloader on compatibility profile load
// note that this function returns MCI interface as pointer
// so you don't have to, for example, wait for SAMP to load -
// - you can just fill it with nulls and then when SAMP is initialized
// fill with correct data
MCI_EXTERN_API MCI_INTERFACE* MCIInitialize(const MCI_INIT_STRUCT* data);
#endif


#endif