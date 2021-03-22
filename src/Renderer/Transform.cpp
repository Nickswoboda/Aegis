#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Aegis{
	
	Transform::Transform(Vec2 pos, float rotation, Vec2 scale)
		:position_(pos), scale_(scale), rotation_(rotation)
	{
		UpdateMatrix();
	}

	void Transform::SetPosition(Vec2 pos)
	{
		position_ = pos;
		UpdateMatrix();
	}

	Vec2 Transform::GetPosition() const
	{
		return position_;
	}

	void Transform::SetRotation(float rotation)
	{
		rotation_ = rotation;
		UpdateMatrix();
	}

	float Transform::GetRotation() const
	{
		return rotation_;
	}

	void Transform::SetScale(Vec2 scale)
	{
		scale_ = scale;
		UpdateMatrix();
	}

	Vec2 Transform::GetScale() const
	{
		return scale_;
	}

	void Transform::SetOrigin(Vec2 origin)
	{
		origin_ = origin;
		UpdateMatrix();
	}

	Vec2 Transform::GetOrigin() const
	{
		return origin_;
	}

	void Transform::UpdateMatrix()
	{
		matrix_ = glm::translate(glm::mat4(1.0f), glm::vec3(position_.x, position_.y, 0.0f));

		//move origin to center of sprite, rotate, then move back
		matrix_ = glm::translate(matrix_, glm::vec3(origin_.x, origin_.y, 0.0f));
		matrix_ = glm::rotate(matrix_, glm::radians(rotation_), glm::vec3(0.0f, 0.0f, 1.0f));
		matrix_ = glm::translate(matrix_, glm::vec3(-origin_.x, -origin_.y, 0.0f));
		matrix_ = glm::scale(matrix_, glm::vec3(scale_.x, scale_.y, 1.0f));
	}

	const glm::mat4& Transform::GetMatrix() const
	{
		return matrix_;
	}
}
