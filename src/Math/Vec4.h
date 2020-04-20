#pragma once

namespace Aegis
{
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

	bool operator==(const Vec4& a, const Vec4& b);
	Vec4 operator+(Vec4 a, const Vec4& b);
	Vec4 operator-(Vec4 a, const Vec4& b);
	Vec4 operator*(Vec4 a, const Vec4& b);
	Vec4 operator*(Vec4 a, float val);
	Vec4 operator/(Vec4 a, const Vec4& b);
	Vec4 operator/(Vec4 a, float val);
};