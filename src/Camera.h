#pragma once

#include <glm/glm.hpp>
namespace Aegis
{
	class Camera
	{
	public:
		Camera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);
		void SetPosition(const glm::vec3& position) { position_ = position; RecalculateViewMatrix(); }
		void RecalculateViewMatrix();
		glm::mat4 view_projection_matrix_;
	private:
		glm::mat4 projection_matrix_;
		glm::mat4 view_matrix_;

		glm::vec3 position_;
	};
}