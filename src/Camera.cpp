#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
namespace Aegis
{
	Camera::Camera(float left, float right, float bottom, float top)
		:projection_matrix_(glm::ortho(left, right, bottom, top)), view_matrix_(glm::mat4(1.0f))
	{
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}
	void Camera::SetProjection(float left, float right, float bottom, float top)
	{
		projection_matrix_ = glm::ortho(left, right, bottom, top);
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}
	void Camera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0), position_);

		view_matrix_ = glm::inverse(transform);

		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}
}