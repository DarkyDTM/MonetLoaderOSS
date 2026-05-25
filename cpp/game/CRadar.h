#pragma once
#include "CVector.h"

struct tRadarTrace {
    unsigned int   m_nColour; // see eBlipColour
    unsigned int   m_nEntityHandle;
    CVector        m_vecPos;
    unsigned short m_nCounter;
    float          m_fSphereRadius;
    unsigned short m_nBlipSize;
    void*          m_pEntryExit;
    unsigned char  m_nRadarSprite; // see eRadarSprite
    unsigned char  m_bBright : 1; // It makes use of bright colors. Always set.
    unsigned char  m_bInUse : 1; // It is available.
    unsigned char  m_bShortRange : 1; // It doesn't show permanently on the radar.
    unsigned char  m_bFriendly : 1; // It is affected by BLIP_COLOUR_THREAT.   
    unsigned char  m_bBlipRemain : 1; // It has the priority over the entity (it will still appear after the entity's deletion).
    unsigned char  m_bBlipFade : 1; // Possibly a leftover. Always unset (unused).
    unsigned char  m_nCoordBlipAppearance : 2; // see eBlipAppearance
    unsigned char  m_nBlipDisplay : 2; // see eBlipDisplay
    unsigned char  m_nBlipType : 4; // see eBlipType
};

#include "gta_struct.inl"
namespace CRadar {
inline tRadarTrace* GetRadarTraces() // max 250
{
	return reinterpret_cast<tRadarTrace*>(lib_manager::radar_traces);
}
}
#include "gta_struct.inl"
