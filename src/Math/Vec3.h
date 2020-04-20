#pragma once

namespace Aegis {
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
	bool operator!=(const Vec3& a, const Vec3& b);
	bool operator==(const Vec3& a, const Vec3& b);
	Vec3 operator+(Vec3 a, const Vec3& b);
	Vec3 operator-(Vec3 a, const Vec3& b);
	Vec3 operator*(Vec3 a, const Vec3& b);
	Vec3 operator*(Vec3 a, float val);
	Vec3 operator/(Vec3 a, const Vec3& b);
	Vec3 operator/(Vec3 a, float val);
}