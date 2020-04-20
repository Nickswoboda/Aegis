#pragma once

#include "Vec4.h"

namespace Aegis {
	typedef unsigned char uint8;
	class Color
	{
	public:
		Color(uint8 red, uint8 green, uint8 blue, uint8 alpha = 255)
			: r(red), g(green), b(blue), a(alpha) {}

		Vec4 Normalized()
		{
			return Vec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
		}

		uint8 r;
		uint8 g;
		uint8 b;
		uint8 a;
	};
}