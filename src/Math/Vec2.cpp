#include "Vec2.h"

#include <cmath>
namespace Aegis {
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
	bool operator!=(const Vec2& a, const Vec2& b) { return a.x != b.x || a.y != b.y; }
	bool operator==(const Vec2& a, const Vec2& b){return (a.x == b.x && a.y == b.y);}
	Vec2 operator+(Vec2 a, const Vec2& b) { return a += b; }
	Vec2 operator-(Vec2 a, const Vec2& b) { return a -= b; }
	Vec2 operator*(Vec2 a, const Vec2& b) { return a *= b; }
	Vec2 operator*(Vec2 a, float val) { return a *= val; }
	Vec2 operator/(Vec2 a, const Vec2& b) { return a /= b; }
	Vec2 operator/(Vec2 a, float val) { return a /= val; }
}