#include "Camera.h"

namespace Aegis
{
	Camera::Camera(float left, float right, float bottom, float top)
		:projection_matrix_(OrthographicProjection(left, right, bottom, top))
	{
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}
	void Camera::SetProjection(float left, float right, float bottom, float top)
	{
		projection_matrix_ = OrthographicProjection(left, right, bottom, top);
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}
	void Camera::RecalculateViewMatrix()
	{
		Mat4 transform;
		//invert position translation
		transform.Translate(-position_);
		view_projection_matrix_ = projection_matrix_ * transform;
	}
}
