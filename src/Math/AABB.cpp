#include "AABB.h"

namespace Aegis {
	bool AABBHasCollided(const AABB& aabb_1, const AABB& aabb_2)
	{
		if ((int)aabb_1.pos.x < aabb_2.pos.x + aabb_2.size.x &&
			(int)aabb_1.pos.x + aabb_1.size.x > aabb_2.pos.x &&
			(int)aabb_1.pos.y < aabb_2.pos.y + aabb_2.size.y &&
			(int)aabb_1.pos.y + aabb_1.size.y > aabb_2.pos.y) {
			return true;
		}

		return false;
	}
}