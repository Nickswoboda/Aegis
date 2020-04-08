#pragma once

namespace Aegis
{
	struct Vec2
	{
		Vec2() = default;
		Vec2(float x, float y)
			: x(x), y(y) {}
		float x = 0;
		float y = 0;
	};

	struct Vec3
	{
		Vec3() = default;
		Vec3(float x, float y, float z)
			: x(x), y(y), z(z) {}
		float x = 0;
		float y = 0;
		float z = 0;
	};

	struct Vec4
	{
		Vec4() = default;
		Vec4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w) {}
		float x = 0;
		float y = 0;
		float z = 0;
		float w = 0;
	};
};