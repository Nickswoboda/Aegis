#pragma once

#include "Vec2.h"

namespace Aegis {
	struct AABB
	{
		AABB() = default;
		AABB(float x, float y, float w, float h)
			: pos{ x, y }, size{ w, h } {}
		Vec2 pos;
		Vec2 size;
	};

	bool AABBHasCollided(const AABB& aabb_1, const AABB& aabb_2);
}