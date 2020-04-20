#pragma once

namespace Aegis {
	typedef unsigned char uint8;
	class Color
	{
	public:
		Color(uint8 red, uint8 green, uint8 blue, uint8 alpha = 255)
			: r(red), g(green), b(blue), a(alpha) {}

		uint8 r;
		uint8 g;
		uint8 b;
		uint8 a;
	};
}