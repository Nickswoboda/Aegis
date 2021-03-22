#pragma once

#include "../Math/Vec2.h"

#include <glm/glm.hpp>

namespace Aegis{

	class Transform
	{
	public:
		Transform() = default;
		Transform(Vec2 pos, float rotation, Vec2 scale);

		void SetPosition(Vec2 position);
		void SetRotation(float rotation);
		void SetScale(Vec2 scale);
		void SetOrigin(Vec2 origin);

		Vec2 GetPosition() const;
		float GetRotation() const;
		Vec2 GetScale() const;
		Vec2 GetOrigin() const;

		const glm::mat4& GetMatrix() const;

	private:
		void UpdateMatrix();

		glm::mat4 matrix_{};
		Vec2 position_{};
		Vec2 scale_{1.0f, 1.0f};
		Vec2 origin_{};
		float rotation_ = 0.0f;
	};
}

