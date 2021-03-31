#pragma once

#include "functional"

namespace Aegis {
	struct Vec2
	{
	public:
		Vec2() = default;
		Vec2(float x, float y)
			: x(x), y(y) {}

		void Normalize();
		Vec2 Normalized();
		Vec2 operator-();
		Vec2& operator+=(const Vec2& other);
		Vec2& operator-=(const Vec2& other);
		Vec2& operator*=(const Vec2& other);
		Vec2& operator*=(float val);
		Vec2& operator/=(const Vec2& other);
		Vec2& operator/=(float val);

		float x = 0;
		float y = 0;
	};

	bool operator!=(const Vec2& a, const Vec2& b);
	bool operator==(const Vec2& a, const Vec2& b);
	Vec2 operator+(Vec2 a, const Vec2& b);
	Vec2 operator-(Vec2 a, const Vec2& b);
	Vec2 operator*(Vec2 a, const Vec2& b);
	Vec2 operator*(Vec2 a, float val);
	Vec2 operator/(Vec2 a, const Vec2& b);
	Vec2 operator/(Vec2 a, float val);
}

namespace std {
	template<> struct hash<Aegis::Vec2>
	{
		std::size_t operator()(const Aegis::Vec2& vec) const
		{
			auto hasher = std::hash<float>{};
			return hasher(vec.x) ^ (hasher(vec.y) << 1);
		}
	};
}


