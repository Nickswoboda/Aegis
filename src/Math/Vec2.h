#pragma once

namespace Aegis {
	struct Vec2
	{
	public:
		Vec2() = default;
		Vec2(float x, float y)
			: x(x), y(y) {}

		void Normalize();
		Vec2 Normalized();
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