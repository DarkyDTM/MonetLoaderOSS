#pragma once
#include "CVector2D.h"

#include "gta_struct.inl"
namespace CTouchInterface {
inline bool IsTouched(int widgetId, CVector2D* out, int frames)
{
	return GTA_FUNC_AT(IsTouched, lib_manager::ctouchinterface_istouched)(widgetId, out, frames);
}
}
#include "gta_struct.inl"