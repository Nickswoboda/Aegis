#include "Math.h"

#include <cmath>
namespace Aegis {

	bool operator==(const Vec2& a, const Vec2& b)
	{
		return (a.x == b.x && a.y == b.y);
	}
	Vec2 operator+(Vec2 a, const Vec2& b)
	{
		return a += b;
	}
	Vec2 operator-(Vec2 a, const Vec2& b)
	{
		return a -= b;
	}
	Vec2 operator*(Vec2 a, const Vec2& b)
	{
		return a *= b;
	}
	Vec2 operator*(Vec2 a, float val)
	{
		return a *= val;
	}
	Vec2 operator/(Vec2 a, const Vec2& b)
	{
		return a /= b;
	}
	Vec2 operator/(Vec2 a, float val)
	{
		return a /= val;
	}
	bool operator==(const Vec3& a, const Vec3& b)
	{
		return (a.x == b.x && a.y == b.y && a.z == b.z);
	}
	Vec3 operator+(Vec3 a, const Vec3& b)
	{
		return a += b;
	}
	Vec3 operator-(Vec3 a, const Vec3& b)
	{
		return a -= b;
	}
	Vec3 operator*(Vec3 a, const Vec3& b)
	{
		return a *= b;
	}
	Vec3 operator*(Vec3 a, float val)
	{
		return a *= val;
	}
	Vec3 operator/(Vec3 a, const Vec3& b)
	{
		return a /= b;
	}
	Vec3 operator/(Vec3 a, float val)
	{
		return a /= val;
	}
	bool operator==(const Vec4& a, const Vec4& b)
	{
		return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
	}
	Vec4 operator+(Vec4 a, const Vec4& b)
	{
		return a += b;
	}
	Vec4 operator-(Vec4 a, const Vec4& b)
	{
		return a -= b;
	}
	Vec4 operator*(Vec4 a, const Vec4& b)
	{
		return a *= b;
	}
	Vec4 operator*(Vec4 a, float val)
	{
		return a *= val;
	}
	Vec4 operator/(Vec4 a, const Vec4& b)
	{
		return a /= b;
	}
	Vec4 operator/(Vec4 a, float val)
	{
		return a /= val;
	}
	void Vec2::Normalize()
	{
		float length = x * x + y * y;
		if (length != 0) {
			length = sqrt(length);
			x /= length;
			y /= length;
		}
	}
	Vec2 Vec2::Normalized()
	{
		Vec2 temp = *this;
		temp.Normalize();
		return temp;
	}
	Vec2& Vec2::operator+=(const Vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	Vec2& Vec2::operator-=(const Vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vec2& Vec2::operator*=(const Vec2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}
	Vec2& Vec2::operator*=(float val)
	{
		x *= val;
		y *= val;
		return *this;
	}
	Vec2& Vec2::operator/=(const Vec2& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	Vec2& Vec2::operator/=(float val)
	{
		x /= val;
		y /= val;
		return *this;
	}
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
	bool AABBHasCollided(const AABB& aabb_1, const AABB& aabb_2)
	{
		if ((int)aabb_1.pos.x < aabb_2.pos.x + aabb_2.size.x &&
			(int)aabb_1.pos.x + aabb_1.size.x > aabb_2.pos.x &&
			(int)aabb_1.pos.y < aabb_2.pos.y + aabb_2.size.y &&
			(int)aabb_1.pos.y + aabb_1.size.y > aabb_2.pos.y) {
			return true;
		}

		return false;
	}
}