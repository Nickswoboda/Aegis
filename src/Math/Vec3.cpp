#include "Vec3.h"

#include <cmath>
namespace Aegis {

	void Vec3::Normalize()
	{
		float length = x * x + y * y + z * z;
		if (length == 0) {
			x = 0;
			y = 0;
			z = 0;
		}
		else {
			length = sqrt(length);
			x /= length;
			y /= length;
			z /= length;
		}
	}
	Vec3 Vec3::Normalized()
	{
		return Vec3();
	}
	Vec3& Vec3::operator+=(const Vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	Vec3& Vec3::operator-=(const Vec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	Vec3& Vec3::operator*=(const Vec3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}
	Vec3& Vec3::operator*=(float val)
	{
		x *= val;
		y *= val;
		z *= val;
		return *this;
	}
	Vec3& Vec3::operator/=(const Vec3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}
	Vec3& Vec3::operator/=(float val)
	{
		x /= val;
		y /= val;
		z /= val;
		return *this;
	}
	bool operator!=(const Vec3& a, const Vec3& b) { return (a.x != b.x || a.y != b.y || a.z != b.z); }
	bool operator==(const Vec3& a, const Vec3& b) { return (a.x == b.x && a.y == b.y && a.z == b.z); }
	Vec3 operator+(Vec3 a, const Vec3& b) { return a += b; }
	Vec3 operator-(Vec3 a, const Vec3& b) { return a -= b; }
	Vec3 operator*(Vec3 a, const Vec3& b) { return a *= b; }
	Vec3 operator*(Vec3 a, float val) { return a *= val; }
	Vec3 operator/(Vec3 a, const Vec3& b) { return a /= b; }
	Vec3 operator/(Vec3 a, float val) { return a /= val; }
}