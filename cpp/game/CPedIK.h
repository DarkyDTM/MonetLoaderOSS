#pragma once
#include "CVector.h"
struct CPed;

// Return flags from MoveLimb() function
enum MoveLimbResult
{
	CANT_REACH_TARGET,
	HAVENT_REACHED_TARGET,
	REACHED_TARGET
};

struct LimbOrientation
{
public:
	float m_fYaw;
	float m_fPitch;
};

struct LimbMovementInfo 
{
	float maxYaw, minYaw;
	float yawD;
	float maxPitch, minPitch;
	float pitchD;
};

class CPedIK {
public:
	CPed *m_pPed;
	LimbOrientation m_TorsoOrien;
	float m_fSlopePitch;
	float m_fSlopePitchLimitMult;
	float m_fSlopeRoll;
	float m_fBodyRoll;

	union
	{
		unsigned int m_nFlags;
		struct
		{
			unsigned int bGunReachedTarget : 1;
			unsigned int bTorsoUsed : 1;
			unsigned int bUseArm : 1;
			unsigned int bSlopePitch : 1;
		};
	};
};