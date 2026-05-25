#pragma once
#include <cstdint>

#pragma pack(push, 1)
namespace game::sync {
struct keys {
	std::uint8_t keys_primaryFire : 1;
	std::uint8_t keys_horn_crouch : 1;
	std::uint8_t keys_secondaryFire_shoot : 1;
	std::uint8_t keys_accel_zoomOut : 1;
	std::uint8_t keys_enterExitCar : 1;
	std::uint8_t keys_decel_jump : 1; // on foot: jump or zoom in
	std::uint8_t keys_circleRight : 1;
	std::uint8_t keys_aim : 1; // hydra auto aim or on foot aim
	std::uint8_t keys_circleLeft : 1;
	std::uint8_t keys_landingGear_lookback : 1;
	std::uint8_t keys_unknown_walkSlow : 1;
	std::uint8_t keys_specialCtrlUp : 1;
	std::uint8_t keys_specialCtrlDown : 1;
	std::uint8_t keys_specialCtrlLeft : 1;
	std::uint8_t keys_specialCtrlRight : 1;
	std::uint8_t keys_unused : 1;
};

struct onfoot {
	std::int16_t lrAnalog;
	std::int16_t udAnalog;
	union {
		std::uint16_t sKeys;
		struct keys stSampKeys;
	};
	float fPosition[3];
	float fQuaternion[4];
	std::uint8_t byteHealth;
	std::uint8_t byteArmor;
	std::uint8_t byteCurrentWeapon;
	std::uint8_t byteSpecialAction;
	float fMoveSpeed[3];
	float fSurfingOffsets[3];
	std::uint16_t sSurfingVehicleID;
	std::uint16_t sCurrentAnimationID;
	std::uint16_t sAnimFlags;
};

struct vehicle {
	std::uint16_t sVehicleID;
	std::int16_t lrAnalog;
	std::int16_t udAnalog;
	union {
		std::uint16_t sKeys;
		struct keys stSampKeys;
	};
	float fQuaternion[4];
	float fPosition[3];
	float fMoveSpeed[3];
	float fVehicleHealth;
	std::uint8_t bytePlayerHealth;
	std::uint8_t bytePlayerArmor;
	std::uint8_t byteCurrentWeapon;
	std::uint8_t byteSiren;
	std::uint8_t byteLandingGearState;
	std::uint16_t sTrailerID;
	union {
		std::uint16_t HydraThrustAngle[2]; // nearly same value
		float fTrainSpeed;
	};
};

struct aim {
	std::uint8_t byteCamMode;
	float vecAimf1[3];
	float vecAimPos[3];
	float fAimZ;
	std::uint8_t byteCamExtZoom : 6; // 0-63 normalized
	std::uint8_t byteWeaponState : 2; // see eWeaponState
	std::uint8_t byteAspectRatio;
};

struct trailer {
	std::uint16_t sTrailerID;
	float fPosition[3];
	float fQuaternion[4];
	float fSpeed[3];
	float fUnk[2];
	std::uint32_t pad;
};

struct passenger {
	std::uint16_t sVehicleID;
	std::uint8_t byteSeatID;
	std::uint8_t byteCurrentWeapon;
	std::uint8_t bytePlayerHealth;
	std::uint8_t bytePlayerArmor;
	std::uint16_t lrAnalog;
	std::uint16_t udAnalog;
	union {
		std::uint16_t sKeys;
		struct keys stSampKeys;
	};
	float fPosition[3];
};

struct damage {
	std::uint16_t sVehicleID_lastDamageProcessed;
	std::int32_t iBumperDamage;
	std::int32_t iDoorDamage;
	std::uint8_t byteLightDamage;
	std::uint8_t byteWheelDamage;
};

struct unoccupied {
	std::uint16_t sVehicleID;
	std::uint8_t byteSeatID;
	float fRoll[3];
	float fDirection[3];
	float fPosition[3];
	float fMoveSpeed[3];
	float fTurnSpeed[3];
	float fHealth;
};

struct bullet {
	std::uint8_t byteType;
	std::uint16_t sTargetID;
	float fOrigin[3];
	float fTarget[3];
	float fCenter[3];
	std::uint8_t byteWeaponID;
};

struct spectator {
	std::uint16_t lrAnalog;
	std::uint16_t udAnalog;
	union {
		std::uint16_t sKeys;
		struct keys SampKeys;
	};
	float fPosition[3];
};

struct spawn {
	std::uint8_t byteTeam;
	std::int32_t iSkin;
	std::uint8_t unk;
	float vecPos[3];
	float fRotation;
	std::int32_t iSpawnWeapons[3];
	std::int32_t iSpawnWeaponsAmmo[3];
};
}
#pragma pack(pop)