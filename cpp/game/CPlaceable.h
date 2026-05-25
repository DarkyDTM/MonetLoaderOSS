#pragma once
#include "CVector.h"
#include "CMatrix.h"

struct CPlaceable
{
	void** vtbl;
	CVector m_vPosn;
	float m_fHeading;
	CMatrix* m_matrix;

	inline CVector &GetPosition()
	{
		return m_matrix ? m_matrix->pos : m_vPosn;
	}
	inline float GetHeading()
	{
		return m_matrix ? std::atan2(-m_matrix->up.x, m_matrix->up.y) : m_fHeading;
	}
};