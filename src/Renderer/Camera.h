#pragma once

#include "../Math/Vec2.h"
#include "../Math/Mat4.h"

namespace Aegis
{
	class Camera
	{
	public:
		Camera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);
		void SetPosition(const Vec2& position) { position_ = position; RecalculateViewMatrix(); }
		void RecalculateViewMatrix();
		Mat4 view_projection_matrix_;
	private:
		Mat4 projection_matrix_;
		Mat4 view_matrix_;

		Vec2 position_;
	};
}
