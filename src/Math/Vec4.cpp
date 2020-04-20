#include "Vec4.h"

namespace Aegis {
	Vec4& Vec4::operator+=(const Vec4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}
	Vec4& Vec4::operator-=(const Vec4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}
	Vec4& Vec4::operator*=(const Vec4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}
	Vec4& Vec4::operator*=(float val)
	{
		x *= val;
		y *= val;
		z *= val;
		w *= val;
		return *this;
	}
	Vec4& Vec4::operator/=(const Vec4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}
	Vec4& Vec4::operator/=(float val)
	{
		x /= val;
		y /= val;
		z /= val;
		w /= val;
		return *this;
	}

	bool operator==(const Vec4& a, const Vec4& b) { return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w); }
	Vec4 operator+(Vec4 a, const Vec4& b) { return a += b; }
	Vec4 operator-(Vec4 a, const Vec4& b) { return a -= b; }
	Vec4 operator*(Vec4 a, const Vec4& b) { return a *= b; }
	Vec4 operator*(Vec4 a, float val) { return a *= val; }
	Vec4 operator/(Vec4 a, const Vec4& b) { return a /= b; }
	Vec4 operator/(Vec4 a, float val) { return a /= val; }
}