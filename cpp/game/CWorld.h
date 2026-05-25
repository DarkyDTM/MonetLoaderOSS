#pragma once
#include "CColPoint.h"
#include "CEntity.h"
#include "CVector.h"

#include "gta_struct.inl"
#include "lib_manager.h"
namespace CWorld {
inline bool ProcessLineOfSight(const CVector& vecStart, const CVector& vecEnd, CColPoint& colPoint, CEntity*& refEntityPtr,
    bool bCheckBuildings, bool bCheckVehicles, bool bCheckPeds, bool bCheckObjects, bool bCheckDummies, bool bSeeThroughStuff,
    bool bIgnoreSomeObjectsForCamera, bool bShootThroughStuff)
{
  return GTA_FUNC_AT(ProcessLineOfSight, lib_manager::process_line_of_sight)(vecStart, vecEnd, colPoint, refEntityPtr,
      bCheckBuildings, bCheckVehicles, bCheckPeds, bCheckObjects, bCheckDummies, bSeeThroughStuff, bIgnoreSomeObjectsForCamera, bShootThroughStuff);
}
}
#include "gta_struct.inl"
