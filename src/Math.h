#pragma once

namespace Aegis
{
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

	struct Vec3
	{
		Vec3() = default;
		Vec3(float x, float y, float z)
			: x(x), y(y), z(z) {}

		void Normalize();
		Vec3 Normalized();
		Vec3& operator+=(const Vec3& other);
		Vec3& operator-=(const Vec3& other);
		Vec3& operator*=(const Vec3& other);
		Vec3& operator*=(float val);
		Vec3& operator/=(const Vec3& other);
		Vec3& operator/=(float val);

		float x = 0;
		float y = 0;
		float z = 0;
	};

	struct Vec4
	{
		Vec4() = default;
		Vec4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w) {}

		Vec4& operator+=(const Vec4& other);
		Vec4& operator-=(const Vec4& other);
		Vec4& operator*=(const Vec4& other);
		Vec4& operator*=(float val);
		Vec4& operator/=(const Vec4& other);
		Vec4& operator/=(float val);


		float x = 0;
		float y = 0;
		float z = 0;
		float w = 0;
	};

	struct AABB
	{
		AABB() = default;
		AABB(float x, float y, float w, float h)
			: pos{ x, y }, size{ w, h } {}
		Vec2 pos;
		Vec2 size;
	};

	bool AABBHasCollided(const AABB& aabb_1, const AABB& aabb_2);

	bool operator==(const Vec2& a, const Vec2& b);
	Vec2 operator+(Vec2 a, const Vec2& b);
	Vec2 operator-(Vec2 a, const Vec2& b);
	Vec2 operator*(Vec2 a, const Vec2& b);
	Vec2 operator*(Vec2 a, float val);
	Vec2 operator/(Vec2 a, const Vec2& b);
	Vec2 operator/(Vec2 a, float val);


	bool operator==(const Vec3& a, const Vec3& b);
	Vec3 operator+(Vec3 a, const Vec3& b);
	Vec3 operator-(Vec3 a, const Vec3& b);
	Vec3 operator*(Vec3 a, const Vec3& b);
	Vec3 operator*(Vec3 a, float val);
	Vec3 operator/(Vec3 a, const Vec3& b);
	Vec3 operator/(Vec3 a, float val);

	bool operator==(const Vec4& a, const Vec4& b);
	Vec4 operator+(Vec4 a, const Vec4& b);
	Vec4 operator-(Vec4 a, const Vec4& b);
	Vec4 operator*(Vec4 a, const Vec4& b);
	Vec4 operator*(Vec4 a, float val);
	Vec4 operator/(Vec4 a, const Vec4& b);
	Vec4 operator/(Vec4 a, float val);
};