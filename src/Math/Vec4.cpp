#include "Vec4.h"
#include "Mat4.h"

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

	bool operator!=(const Vec4& a, const Vec4& b) { return (a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w); }
	bool operator==(const Vec4& a, const Vec4& b) { return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w); }
	Vec4 operator+(Vec4 a, const Vec4& b) { return a += b; }
	Vec4 operator-(Vec4 a, const Vec4& b) { return a -= b; }
	Vec4 operator*(Vec4 a, const Vec4& b) { return a *= b; }
	Vec4 operator*(Vec4 a, float val) { return a *= val; }
	Vec4 operator/(Vec4 a, const Vec4& b) { return a /= b; }
	Vec4 operator/(Vec4 a, float val) { return a /= val; }

	Vec4 operator*(const Vec4& vec, const Mat4& m)
	{
		auto matrix = m.elements;
		return {
			matrix[0][0] * vec.x + matrix[0][1] * vec.y + matrix[0][2] * vec.z + matrix[0][3] * vec.w,
			matrix[1][0] * vec.x + matrix[1][1] * vec.y + matrix[1][2] * vec.z + matrix[1][3] * vec.w,
			matrix[2][0] * vec.x + matrix[2][1] * vec.y + matrix[2][2] * vec.z + matrix[2][3] * vec.w,
			matrix[3][0] * vec.x + matrix[3][1] * vec.y + matrix[3][2] * vec.z + matrix[3][3] * vec.w,
		};
	}
}
