#pragma once
#include <cmath>

class CVector
{
public:
	float x, y, z;

	[[nodiscard]] float Length() const
	{
		return static_cast<float>(std::sqrt(x * x + y * y + z * z));
	}
	[[nodiscard]] float LengthSquared() const
	{
		return static_cast<float>(x * x + y * y + z * z);
	}
	[[nodiscard]] float Distance(const CVector& v) const
	{
		float a = x - v.x;
		float b = y - v.y;
		float c = z - v.z;
		return static_cast<float>(std::sqrt(a * a + b * b + c * c));
	}
	[[nodiscard]] float DistanceSquared(const CVector& v) const
	{
		float a = x - v.x;
		float b = y - v.y;
		float c = z - v.z;
		return static_cast<float>(a * a + b * b + c * c);
	}
	[[nodiscard]] float Angle(const CVector& v) const
	{
		return static_cast<float>(std::acos(Dot(v) / Length() * v.Length()));
	}
	[[nodiscard]] float Dot(const CVector& v) const
	{
		return static_cast<float>(x * v.x + y * v.y + z * v.z);
	}
	void Cross(const CVector& v)
	{
		float a = y * v.z - v.y * z;
		float b = z * v.x - v.z * x;
		float c = x * v.y - v.x * y;
		x = a; y = b; z = c;
	}
	void Normalize()
	{
		auto len = Length();
		x /= len;
		y /= len;
		z /= len;
	}
	CVector Normalized()
	{
		auto len = Length();
		return { x / len, y / len, z / len };
	}

	bool operator==(const CVector& rhs)
	{
		return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
	}
	bool operator!=(const CVector& rhs)
	{
		return !(*this == rhs);
	}

	CVector& operator*=(const CVector& rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
		return *this;
	}
	CVector& operator/=(const CVector& rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		this->z /= rhs.z;
		return *this;
	}
	CVector& operator+=(const CVector& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		return *this;
	}
	CVector& operator-=(const CVector& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		return *this;
	}

	CVector& operator*=(const float rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;
		return *this;
	}
	CVector& operator/=(const float rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;
		return *this;
	}
	CVector& operator+=(const float rhs)
	{
		this->x += rhs;
		this->y += rhs;
		this->z += rhs;
		return *this;
	}
	CVector& operator-=(const float rhs)
	{
		this->x -= rhs;
		this->y -= rhs;
		this->z -= rhs;
		return *this;
	}

	CVector operator-()
	{
		return CVector{ -x, -y, -z };
  }

	friend CVector operator*(CVector lhs, const CVector& rhs)
	{
		lhs *= rhs;
		return lhs;
	}
	friend CVector operator/(CVector lhs, const CVector& rhs)
	{
		lhs /= rhs;
		return lhs;
	}
	friend CVector operator+(CVector lhs, const CVector& rhs)
	{
		lhs += rhs;
		return lhs;
	}
	friend CVector operator-(CVector lhs, const CVector& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	friend CVector operator*(CVector lhs, const float rhs)
	{
		lhs *= rhs;
		return lhs;
	}
	friend CVector operator/(CVector lhs, const float rhs)
	{
		lhs /= rhs;
		return lhs;
	}
	friend CVector operator+(CVector lhs, const float rhs)
	{
		lhs += rhs;
		return lhs;
	}
	friend CVector operator-(CVector lhs, const float rhs)
	{
		lhs -= rhs;
		return lhs;
	}
};