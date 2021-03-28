#include "Mat4.h"

#include <cmath>

namespace Aegis{

	const Mat4 Mat4::Identity;

	Mat4::Mat4()
		: elements{{1.0f, 0.0f, 0.0f, 0.0f},
			       {0.0f, 1.0f, 0.0f, 0.0f},
				   {0.0f, 0.0f, 1.0f, 0.0f},
				   {0.0f, 0.0f, 0.0f, 1.0f}}
	{}

	Mat4::Mat4(float e00, float e01, float e02, float e03,
			   float e10, float e11, float e12, float e13,
			   float e20, float e21, float e22, float e23,
			   float e30, float e31, float e32, float e33)
		: elements{ {e00, e01, e02, e03},
			        {e10, e11, e12, e13},
					{e20, e21, e22, e23},
					{e30, e31, e32, e33}}
	{}

	Mat4& Mat4::operator *=(const Mat4& matrix)
	{
		const auto a = elements;
		const auto b = matrix.elements;

		*this = Mat4(
			a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0] + a[0][3] * b[3][0],
			a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1] + a[0][3] * b[3][1],
			a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2] + a[0][3] * b[3][2],
			a[0][0] * b[0][3] + a[0][1] * b[1][3] + a[0][2] * b[2][3] + a[0][3] * b[3][3],
			a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0] + a[1][3] * b[3][0],
			a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1] + a[1][3] * b[3][1],
			a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2] + a[1][3] * b[3][2],
			a[1][0] * b[0][3] + a[1][1] * b[1][3] + a[1][2] * b[2][3] + a[1][3] * b[3][3],
			a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0] + a[2][3] * b[3][0],
			a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1] + a[2][3] * b[3][1],
			a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2] + a[2][3] * b[3][2],
			a[2][0] * b[0][3] + a[2][1] * b[1][3] + a[2][2] * b[2][3] + a[2][3] * b[3][3],
			a[3][0] * b[0][0] + a[3][1] * b[1][0] + a[3][2] * b[2][0] + a[3][3] * b[3][0],
			a[3][0] * b[0][1] + a[3][1] * b[1][1] + a[3][2] * b[2][1] + a[3][3] * b[3][1],
			a[3][0] * b[0][2] + a[3][1] * b[1][2] + a[3][2] * b[2][2] + a[3][3] * b[3][2],
			a[3][0] * b[0][3] + a[3][1] * b[1][3] + a[3][2] * b[2][3] + a[3][3] * b[3][3]
		);

		return *this;
	}

	void Mat4::Translate(Vec2 translation)
	{
		Mat4 matrix = {1, 0, 0, translation.x,
					   0, 1, 0, translation.y,
					   0, 0, 1, 0,
					   0, 0, 0, 1};

		*this *= matrix;
	}

	void Mat4::Rotate(float degrees)
	{
		float radians = degrees * (3.141592654f / 180);
		float cos = std::cos(radians);
		float sin = std::sin(radians);

		Mat4 matrix = {cos, -sin, 0, 0,
					   sin, cos, 0, 0,
					   0, 0, 1, 0,
					   0, 0, 0, 1};

		*this *= matrix;


	}

	void Mat4::Scale(Vec2 scale){

		Mat4 matrix = {scale.x, 0, 0, 0,
					   0, scale.y, 0, 0,
					   0, 0, 1, 0,
					   0, 0, 0, 1};

		*this *= matrix;
	}


}
