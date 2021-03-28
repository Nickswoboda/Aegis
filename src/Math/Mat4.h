#pragma once

#include "Vec2.h"

namespace Aegis{
	
	class Mat4
	{
	public:
		Mat4();
		Mat4(float e00, float e01, float e02, float e03,
			 float e10, float e11, float e12, float e13,
			 float e20, float e21, float e22, float e23,
			 float e30, float e31, float e32, float e33);

		static const Mat4 Identity;

		void Translate(Vec2 translation);
		void Rotate(float degrees);
		void Scale(Vec2 scale);

		Mat4& operator *=(const Mat4& matrix);

		float elements[4][4];

	};

	Mat4 operator*(const Mat4& matrix);
}
