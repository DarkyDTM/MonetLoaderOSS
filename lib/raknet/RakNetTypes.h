/// \file
/// \brief Types used by RakNet, most of which involve user code.
///
/// This file is part of RakNet Copyright 2003 Kevin Jenkins.
///
/// Usage of RakNet is subject to the appropriate license agreement.
/// Creative Commons Licensees are subject to the
/// license found at
/// http://creativecommons.org/licenses/by-nc/2.5/
/// Single application licensees are subject to the license found at
/// http://www.rakkarsoft.com/SingleApplicationLicense.html
/// Custom license users are subject to the terms therein.
/// GPL license users are subject to the GNU General Public
/// License as published by the Free
/// Software Foundation; either version 2 of the License, or (at your
/// option) any later version.
#pragma once

/// Given a number of bits, return how many bytes are needed to represent that.
#define SAMP_BITS_TO_BYTES(x) (((x) + 7) >> 3)
#define SAMP_BYTES_TO_BITS(x) ((x) << 3)

/// Forward declaration
namespace RakNet {
class BitStream;

/// \sa NetworkIDGenerator.h
typedef unsigned char UniqueIDType;
typedef unsigned short PlayerIndex;
typedef unsigned char RPCIndex;
const int MAX_RPC_MAP_SIZE = ((RPCIndex)-1) - 1;
const int UNDEFINED_RPC_INDEX = ((RPCIndex)-1);

/// First byte of a network message
typedef unsigned char MessageID;

// Define __GET_TIME_64BIT if you want to use large types for GetTime (takes more bandwidth when you transmit time though!)
// You would want to do this if your system is going to run long enough to overflow the millisecond counter (over a month)
#ifdef __GET_TIME_64BIT
typedef long long RakNetTime;
typedef long long RakNetTimeNS;
#else
typedef unsigned int RakNetTime;
typedef long long RakNetTimeNS;
#endif

/// \brief Unique identifier for a system.
/// Corresponds to a network address
struct PlayerID {
	/// The peer address from inet_addr.
	unsigned int binaryAddress;
	/// The port number
	unsigned short port;
};

struct NetworkID {
	// In peer to peer, we use both playerId and localSystemId
	// In client / server, we only use localSystemId
	PlayerID playerId;
	unsigned short localSystemId;
};

/// This represents a user message from another system.
struct Packet {
	/// Server only - this is the index into the player array that this playerId maps to
	PlayerIndex playerIndex;

	/// The system that send this packet.
	PlayerID playerId;

	/// The length of the data in bytes
	/// \deprecated You should use bitSize.
	unsigned int length;

	/// The length of the data in bits
	unsigned int bitSize;

	/// The data from the sender
	unsigned char* data;

	/// @internal
	/// Indicates whether to delete the data, or to simply delete the packet.
	bool deleteData;
};

/// All RPC functions have the same parameter list - this structure.
struct RPCParameters {
	/// The data from the remote system
	unsigned char* input;

	/// How many bits long \a input is
	unsigned int numberOfBitsOfData;

	/// Which system called this RPC
	PlayerID sender;

	/// Which instance of RakPeer (or a derived RakServer or RakClient) got this call
	void* recipient;

	// TODO - RakNet 3.0. Be consistent and have user put ID_TIMESTAMP, rather than do this
	// Bug: hasTimestamp was unused.
	// bool hasTimestamp;

	/// You can return values from RPC calls by writing them to this BitStream.
	/// This is only sent back if the RPC call originally passed a BitStream to receive the reply.
	/// If you do so and your send is reliable, it will block until you get a reply or you get disconnected from the system you are sending to, whichever is first.
	/// If your send is not reliable, it will block for triple the ping time, or until you are disconnected, or you get a reply, whichever is first.
	RakNet::BitStream* replyToSender;
};

///  Index of an unassigned player
const PlayerIndex UNASSIGNED_PLAYER_INDEX = 65535;

/// Index of an invalid PlayerID
const PlayerID UNASSIGNED_PLAYER_ID = {
	0xFFFFFFFF, 0xFFFF
};

/// Unassigned object ID
const NetworkID UNASSIGNED_NETWORK_ID = {
	{ 0xFFFFFFFF, 0xFFFF }, 65535
};

const int PING_TIMES_ARRAY_SIZE = 5;

enum RPCEnumeration {
	RPC_ClickPlayer = 23,
	RPC_ClientJoin = 25,
	RPC_EnterVehicle = 26,
	RPC_EnterEditObject = 27,
	RPC_ScriptCash = 31,
	RPC_ServerCommand = 50,
	RPC_Spawn = 52,
	RPC_Death = 53,
	RPC_NPCJoin = 54,
	RPC_DialogResponse = 62,
	RPC_ClickTextDraw = 83,
	RPC_ScmEvent = 96,
	RPC_WeaponPickupDestroy = 97,
	RPC_Chat = 101,
	RPC_SrvNetStats = 102,
	RPC_ClientCheck = 103,
	RPC_DamageVehicle = 106,
	RPC_GiveTakeDamage = 115,
	RPC_EditAttachedObject = 116,
	RPC_EditObject = 117,
	RPC_SetInteriorId = 118,
	RPC_MapMarker = 119,
	RPC_RequestClass = 128,
	RPC_RequestSpawn = 129,
	RPC_PickedUpPickup = 131,
	RPC_MenuSelect = 132,
	RPC_VehicleDestroyed = 136,
	RPC_MenuQuit = 140,
	RPC_ExitVehicle = 154,
	RPC_UpdateScoresPingsIPs = 155
};

enum ScriptRPCEnumeration {
  RPC_ScrSetPlayerName = 11,
  RPC_ScrSetPlayerPos = 12,
  RPC_ScrSetPlayerPosFindZ = 13,
  RPC_ScrSetPlayerHealth = 14,
  RPC_ScrTogglePlayerControllable = 15,
  RPC_ScrPlaySound = 16,
  RPC_ScrSetPlayerWorldBounds = 17,
  RPC_ScrGivePlayerMoney = 18,
  RPC_ScrSetPlayerFacingAngle = 19,
  RPC_ScrResetPlayerMoney = 20,
  RPC_ScrResetPlayerWeapons = 21,
  RPC_ScrGivePlayerWeapon = 22,
  RPC_ScrSetVehicleParamsEx = 24,
  RPC_ScrCancelEdit = 28,
  RPC_ScrSetPlayerTime = 29,
  RPC_ScrToggleClock = 30,
  RPC_ScrWorldPlayerAdd = 32,
  RPC_ScrSetPlayerShopName = 33,
  RPC_ScrSetPlayerSkillLevel = 34,
  RPC_ScrSetPlayerDrunkLevel = 35,
  RPC_ScrCreate3DTextLabel = 36,
  RPC_ScrDisableCheckpoint = 37,
  RPC_ScrSetRaceCheckpoint = 38,
  RPC_ScrDisableRaceCheckpoint = 39,
  RPC_ScrGameModeRestart = 40,
  RPC_ScrPlayAudioStream = 41,
  RPC_ScrStopAudioStream = 42,
  RPC_ScrRemoveBuildingForPlayer = 43,
  RPC_ScrCreateObject = 44,
  RPC_ScrSetObjectPos = 45,
  RPC_ScrSetObjectRot = 46,
  RPC_ScrDestroyObject = 47,
  RPC_ScrDeathMessage = 55,
  RPC_ScrSetPlayerMapIcon = 56,
  RPC_ScrRemoveVehicleComponent = 57,
  RPC_ScrDestroy3DTextLabel = 58,
  RPC_ScrChatBubble = 59,
  RPC_ScrSomeupdate = 60,
  RPC_ScrShowDialog = 61,
  RPC_ScrDestroyPickup = 63,
  RPC_ScrLinkVehicleToInterior = 65,
  RPC_ScrSetPlayerArmour = 66,
  RPC_ScrSetPlayerArmedWeapon = 67,
  RPC_ScrSetSpawnInfo = 68,
  RPC_ScrSetPlayerTeam = 69,
  RPC_ScrPutPlayerInVehicle = 70,
  RPC_ScrRemovePlayerFromVehicle = 71,
  RPC_ScrSetPlayerColor = 72,
  RPC_ScrDisplayGameText = 73,
  RPC_ScrForceClassSelection = 74,
  RPC_ScrAttachObjectToPlayer = 75,
  RPC_ScrInitMenu = 76,
  RPC_ScrShowMenu = 77,
  RPC_ScrHideMenu = 78,
  RPC_ScrCreateExplosion = 79,
  RPC_ScrShowPlayerNameTagForPlayer = 80,
  RPC_ScrAttachCameraToObject = 81,
  RPC_ScrInterpolateCamera = 82,
  RPC_ScrSetObjectMaterial = 84,
  RPC_ScrGangZoneStopFlash = 85,
  RPC_ScrApplyAnimation = 86,
  RPC_ScrClearAnimations = 87,
  RPC_ScrSetPlayerSpecialAction = 88,
  RPC_ScrSetPlayerFightingStyle = 89,
  RPC_ScrSetPlayerVelocity = 90,
  RPC_ScrSetVehicleVelocity = 91,
  RPC_ScrClientMessage = 93,
  RPC_ScrSetWorldTime = 94,
  RPC_ScrCreatePickup = 95,
  RPC_ScrMoveObject = 99,
  RPC_ScrEnableStuntBonusForPlayer = 104,
  RPC_ScrTextDrawSetString = 105,
  RPC_ScrSetCheckpoint = 107,
  RPC_ScrGangZoneCreate = 108,
  RPC_ScrPlayCrimeReport = 112,
  RPC_ScrSetPlayerAttachedObject = 113,
  RPC_ScrGangZoneDestroy = 120,
  RPC_ScrGangZoneFlash = 121,
  RPC_ScrStopObject = 122,
  RPC_ScrSetNumberPlate = 123,
  RPC_ScrTogglePlayerSpectating = 124,
  RPC_ScrPlayerSpectatePlayer = 126,
  RPC_ScrPlayerSpectateVehicle = 127,
  RPC_ScrSetPlayerWantedLevel = 133,
  RPC_ScrShowTextDraw = 134,
  RPC_ScrTextDrawHideForPlayer = 135,
  RPC_ScrServerJoin = 137,
  RPC_ScrServerQuit = 138,
  RPC_ScrInitGame = 139,
  RPC_ScrRemovePlayerMapIcon = 144,
  RPC_ScrSetPlayerAmmo = 145,
  RPC_ScrSetGravity = 146,
  RPC_ScrSetVehicleHealth = 147,
  RPC_ScrAttachTrailerToVehicle = 148,
  RPC_ScrDetachTrailerFromVehicle = 149,
  RPC_ScrSetWeather = 152,
  RPC_ScrSetPlayerSkin = 153,
  RPC_ScrSetPlayerInterior = 156,
  RPC_ScrSetPlayerCameraPos = 157,
  RPC_ScrSetPlayerCameraLookAt = 158,
  RPC_ScrSetVehiclePos = 159,
  RPC_ScrSetVehicleZAngle = 160,
  RPC_ScrSetVehicleParamsForPlayer = 161,
  RPC_ScrSetCameraBehindPlayer = 162,
  RPC_ScrWorldPlayerRemove = 163,
  RPC_ScrWorldVehicleAdd = 164,
  RPC_ScrWorldVehicleRemove = 165,
  RPC_ScrWorldPlayerDeath = 166,
  RPC_ScrCreateActor = 171,
  RPC_ScrDestroyActor = 172
};

enum PacketEnumeration {
	ID_INTERNAL_PING = 6,
	ID_PING,
	ID_PING_OPEN_CONNECTIONS,
	ID_CONNECTED_PONG,
	ID_REQUEST_STATIC_DATA,
	ID_CONNECTION_REQUEST,
	ID_AUTH_KEY,
	ID_BROADCAST_PINGS = 14,
	ID_SECURED_CONNECTION_RESPONSE,
	ID_SECURED_CONNECTION_CONFIRMATION,
	ID_RPC_MAPPING,
	ID_SET_RANDOM_NUMBER_SEED = 19,
	ID_RPC,
	ID_RPC_REPLY,
	ID_DETECT_LOST_CONNECTIONS = 23,
	ID_OPEN_CONNECTION_REQUEST,
	ID_OPEN_CONNECTION_REPLY,
	ID_CONNECTION_COOKIE,
	ID_RSA_PUBLIC_KEY_MISMATCH = 28,
	ID_CONNECTION_ATTEMPT_FAILED,
	ID_NEW_INCOMING_CONNECTION,
	ID_NO_FREE_INCOMING_CONNECTIONS,
	ID_DISCONNECTION_NOTIFICATION,
	ID_CONNECTION_LOST,
	ID_CONNECTION_REQUEST_ACCEPTED,
	ID_INITIALIZE_ENCRYPTION,
	ID_CONNECTION_BANNED,
	ID_INVALID_PASSWORD,
	ID_MODIFIED_PACKET,
	ID_PONG,
	ID_TIMESTAMP,
	ID_RECEIVED_STATIC_DATA,
	ID_REMOTE_DISCONNECTION_NOTIFICATION,
	ID_REMOTE_CONNECTION_LOST,
	ID_REMOTE_NEW_INCOMING_CONNECTION,
	ID_REMOTE_EXISTING_CONNECTION,
	ID_REMOTE_STATIC_DATA,
	ID_ADVERTISE_SYSTEM = 56,

	ID_VEHICLE_SYNC = 200,
	ID_RCON_COMMAND,
	ID_RCON_RESPONSE,
	ID_AIM_SYNC,
	ID_WEAPONS_UPDATE,
	ID_STATS_UPDATE,
	ID_BULLET_SYNC,
	ID_PLAYER_SYNC,
	ID_MARKERS_SYNC,
	ID_UNOCCUPIED_SYNC,
	ID_TRAILER_SYNC,
	ID_PASSENGER_SYNC,
	ID_SPECTATOR_SYNC,
};

/// These enumerations are used to describe when packets are delivered.
enum PacketPriority {
	SYSTEM_PRIORITY, /// \internal Used by RakNet to send above-high priority messages.
	HIGH_PRIORITY, /// High priority messages are send before medium priority messages.
	MEDIUM_PRIORITY, /// Medium priority messages are send before low priority messages.
	LOW_PRIORITY, /// Low priority messages are only sent when no other messages are waiting.
	NUMBER_OF_PRIORITIES
};

/// These enumerations are used to describe how packets are delivered.
/// \note  Note to self: I write this with 3 bits in the stream.  If I add more remember to change that
enum PacketReliability {
	UNRELIABLE = 6, /// Same as regular UDP, except that it will also discard duplicate datagrams.  RakNet adds (6 to 17) + 21 bits of overhead, 16 of which is used to detect duplicate packets and 6 to 17 of which is used for message length.
	UNRELIABLE_SEQUENCED, /// Regular UDP with a sequence counter.  Out of order messages will be discarded.  This adds an additional 13 bits on top what is used for UNRELIABLE.
	RELIABLE, /// The message is sent reliably, but not necessarily in any order.  Same overhead as UNRELIABLE.
	RELIABLE_ORDERED, /// This message is reliable and will arrive in the order you sent it.  Messages will be delayed while waiting for out of order messages.  Same overhead as UNRELIABLE_SEQUENCED.
	RELIABLE_SEQUENCED /// This message is reliable and will arrive in the sequence you sent it.  Out or order messages will be dropped.  Same overhead as UNRELIABLE_SEQUENCED.
};
};