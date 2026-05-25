#pragma once
#include "CPlaceable.h"

enum eEntityType
{
	ENTITY_TYPE_NOTHING,
	ENTITY_TYPE_BUILDING,
	ENTITY_TYPE_VEHICLE,
	ENTITY_TYPE_PED,
	ENTITY_TYPE_OBJECT,
	ENTITY_TYPE_DUMMY,
	ENTITY_TYPE_NOTINPOOLS
};

enum eEntityStatus
{
	STATUS_PLAYER,
	STATUS_PLAYER_PLAYBACKFROMBUFFER,
	STATUS_SIMPLE,
	STATUS_PHYSICS,
	STATUS_ABANDONED,
	STATUS_WRECKED,
	STATUS_TRAIN_MOVING,
	STATUS_TRAIN_NOT_MOVING,
	STATUS_HELI,
	STATUS_PLANE,
	STATUS_REMOTE_CONTROLLED,
	STATUS_PLAYER_DISABLED,
	STATUS_TRAILER,
	STATUS_SIMPLE_TRAILER
};

struct CPhysical;
struct CEntity : public CPlaceable
{
	union {
		uintptr_t m_pRwObject;
		uintptr_t m_pRpClump;
		uintptr_t m_pRpAtomic;
	};
	
	unsigned int m_bUsesCollision : 1;           // does entity use collision
	unsigned int m_bCollisionProcessed : 1;  // has object been processed by a ProcessEntityCollision function
	unsigned int m_bIsStatic : 1;                // is entity static
	unsigned int m_bHasContacted : 1;            // has entity processed some contact forces
	unsigned int m_bIsStuck : 1;             // is entity stuck
	unsigned int m_bIsInSafePosition : 1;        // is entity in a collision free safe position
	unsigned int m_bWasPostponed : 1;            // was entity control processing postponed
	unsigned int m_bIsVisible : 1;               //is the entity visible
 
	unsigned int m_bIsBIGBuilding : 1;           // Set if this entity is a big building
	unsigned int m_bRenderDamaged : 1;           // use damaged LOD models for objects with applicable damage
	unsigned int m_bStreamingDontDelete : 1; // Dont let the streaming remove this 
	unsigned int m_bRemoveFromWorld : 1;     // remove this entity next time it should be processed
	unsigned int m_bHasHitWall : 1;              // has collided with a building (changes subsequent collisions)
	unsigned int m_bImBeingRendered : 1;     // don't delete me because I'm being rendered
	unsigned int m_bDrawLast :1;             // draw object last
	unsigned int m_bDistanceFade :1;         // Fade entity because it is far away
 
	unsigned int m_bDontCastShadowsOn : 1;       // Dont cast shadows on this object
	unsigned int m_bOffscreen : 1;               // offscreen flag. This can only be trusted when it is set to true
	unsigned int m_bIsStaticWaitingForCollision : 1; // this is used by script created entities - they are static until the collision is loaded below them
	unsigned int m_bDontStream : 1;              // tell the streaming not to stream me
	unsigned int m_bUnderwater : 1;              // this object is underwater change drawing order
	unsigned int m_bHasPreRenderEffects : 1; // Object has a prerender effects attached to it
	unsigned int m_bIsTempBuilding : 1;          // whether or not the building is temporary (i.e. can be created and deleted more than once)
	unsigned int m_bDontUpdateHierarchy : 1; // Don't update the aniamtion hierarchy this frame
 
	unsigned int m_bHasRoadsignText : 1;     // entity is roadsign and has some 2deffect text stuff to be rendered
	unsigned int m_bDisplayedSuperLowLOD : 1;
	unsigned int m_bIsProcObject : 1;            // set object has been generate by procedural object generator
	unsigned int m_bBackfaceCulled : 1;          // has backface culling on
	unsigned int m_bLightObject : 1;         // light object with directional lights
	unsigned int m_bUnimportantStream : 1;       // set that this object is unimportant, if streaming is having problems
	unsigned int m_bTunnel : 1;          // Is this model part of a tunnel
	unsigned int m_bTunnelTransition : 1; // This model should be rendered from within and outside of the tunnel

	std::uint32_t m_bdummy; // 2.00

	uint16_t m_nRandomSeed;
	uint16_t nModelIndex;
	void *m_pReferences;
	void *m_pStreamingLink;
	std::uint16_t m_nScanCode;
	char m_nIplIndex;
	unsigned char m_nAreaCode;
	CEntity *m_pLod; // -1 = no lod
	unsigned char m_nNumLodChildren;
	unsigned char m_nNumLodChildrenRendered;
	unsigned char m_nType : 3; // see eEntityType
	unsigned char m_nStatus : 5; // see eEntityStatus
};