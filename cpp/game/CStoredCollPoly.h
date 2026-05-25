#pragma once
#include "CVector.h"

class CStoredCollPoly
{
public:
	CVector      m_aMeshVertices[3]; // triangle vertices
	bool         m_bIsActual;
	unsigned int m_nLighting;
};