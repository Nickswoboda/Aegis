#include "Math.h"

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