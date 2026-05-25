#pragma once
#include "RakNetTypes.h"

class RakClientInterface;
class RakClientInterface_vtbl
{
private:
	void* itanium_dtor1;
	void* itanium_dtor2;
public:
	bool (*Connect)(RakClientInterface* thiz, const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer);
	void (*Disconnect)(RakClientInterface* thiz, unsigned int blockDuration, unsigned char orderingChannel);
	void (*InitializeSecurity)(RakClientInterface* thiz, const char *privKeyP, const char *privKeyQ);
	void (*SetPassword)(RakClientInterface* thiz, const char *password);
	bool (*HasPassword)(RakClientInterface* thiz);
	bool (*SendEx)(RakClientInterface* thiz, const char *data, const int length, RakNet::PacketPriority priority, RakNet::PacketReliability reliability, char orderingChannel);
	bool (*Send)(RakClientInterface* thiz, RakNet::BitStream * bitStream, RakNet::PacketPriority priority, RakNet::PacketReliability reliability, char orderingChannel);
	RakNet::Packet* (*Receive)(RakClientInterface* thiz);
	void (*DeallocatePacket)(RakClientInterface* thiz, RakNet::Packet *packet);
	void (*PingServerEx)(RakClientInterface* thiz);
	void (*PingServer)(RakClientInterface* thiz, const char* host, unsigned short serverPort, unsigned short clientPort, bool onlyReplyOnAcceptingConnections);
	int (*GetAveragePing)(RakClientInterface* thiz);
	int (*GetLastPing)(RakClientInterface* thiz);
	int (*GetLowestPing)(RakClientInterface* thiz);
	int (*GetPlayerPing)(RakClientInterface* thiz, const RakNet::PlayerID playerId);
	void (*StartOccasionalPing)(RakClientInterface* thiz);
	void (*StopOccasionalPing)(RakClientInterface* thiz);
	bool (*IsConnected)(RakClientInterface* thiz);
	unsigned int (*GetSynchronizedRandomInteger)(RakClientInterface* thiz);
	bool (*GenerateCompressionLayer)(RakClientInterface* thiz, unsigned int inputFrequencyTable[256], bool inputLayer);
	bool (*DeleteCompressionLayer)(RakClientInterface* thiz, bool inputLayer);
	void (*RegisterAsRemoteProcedureCall)(RakClientInterface* thiz, int* uniqueID, void(*functionPointer)(RakNet::RPCParameters *rpcParms));
	void (*RegisterClassMemberRPC)(RakClientInterface* thiz, int* uniqueID, void *functionPointer);
	void (*UnregisterAsRemoteProcedureCall)(RakClientInterface* thiz, int* uniqueID);
	bool (*RPCEx)(RakClientInterface* thiz, int* uniqueID, const char* data, unsigned int bitLength, RakNet::PacketPriority priority, RakNet::PacketReliability reliability,
		char orderingChannel, bool shiftTimestamp, RakNet::NetworkID networkID, RakNet::BitStream *replyFromTarget);
	bool (*RPC)(RakClientInterface* thiz, int* uniqueID, RakNet::BitStream* bitStream, RakNet::PacketPriority priority, RakNet::PacketReliability reliability,
		char orderingChannel, bool shiftTimestamp, RakNet::NetworkID networkID, RakNet::BitStream *replyFromTarget);
	void (*SetTrackFrequencyTable)(RakClientInterface* thiz, bool b);
	bool (*GetSendFrequencyTable)(RakClientInterface* thiz, unsigned int outputFrequencyTable[256]);
	float (*GetCompressionRatio)(RakClientInterface* thiz);
	float (*GetDecompressionRatio)(RakClientInterface* thiz);
	void (*AttachPlugin)(RakClientInterface* thiz, void *messageHandler);
	void (*DetachPlugin)(RakClientInterface* thiz, void *messageHandler);
	RakNet::BitStream * (*GetStaticServerData)(RakClientInterface* thiz);
	void (*SetStaticServerData)(RakClientInterface* thiz, const char *data, const int length);
	RakNet::BitStream * (*GetStaticClientDataEx)(RakClientInterface* thiz, const RakNet::PlayerID playerId);
	void (*SetStaticClientDataEx)(RakClientInterface* thiz, const RakNet::PlayerID playerId, const char *data, const int length);
	void (*SendStaticClientDataToServer)(RakClientInterface* thiz);
	RakNet::PlayerID (*GetServerID)(RakClientInterface* thiz);
	RakNet::PlayerID (*GetPlayerID)(RakClientInterface* thiz);
	RakNet::PlayerID (*GetInternalID)(RakClientInterface* thiz);
	const char* (*PlayerIDToDottedIP)(RakClientInterface* thiz, const RakNet::PlayerID playerId);
	void (*PushBackPacket)(RakClientInterface* thiz, RakNet::Packet *packet, bool pushAtHead);
	void (*SetRouterInterface)(RakClientInterface* thiz, void *routerInterface);
	void (*RemoveRouterInterface)(RakClientInterface* thiz, void *routerInterface);
	void (*SetTimeoutTime)(RakClientInterface* thiz, RakNet::RakNetTime timeMS);
	bool (*SetMTUSize)(RakClientInterface* thiz, int size);
	int (*GetMTUSize)(RakClientInterface* thiz);
	void (*AllowConnectionResponseIPMigration)(RakClientInterface* thiz, bool allow);
	void (*AdvertiseSystem)(RakClientInterface* thiz, const char *host, unsigned short remotePort, const char *data, int dataLength);
	void * const (*GetStatistics)(RakClientInterface* thiz);
	void (*ApplyNetworkSimulator)(RakClientInterface* thiz, double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance);
	bool (*IsNetworkSimulatorActive)(RakClientInterface* thiz);
	RakNet::PlayerIndex (*GetPlayerIndex)(RakClientInterface* thiz);
};

class RakClientInterface
{
public:
	RakClientInterface_vtbl* vtbl;
};