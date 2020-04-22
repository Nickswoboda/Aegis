#include "AABB.h"

namespace Aegis {
	bool AABBHasCollided(const AABB& aabb_1, const AABB& aabb_2)
	{
		return ((int)aabb_1.pos.x < aabb_2.pos.x + aabb_2.size.x &&
			(int)aabb_1.pos.x + aabb_1.size.x > aabb_2.pos.x &&
			(int)aabb_1.pos.y < aabb_2.pos.y + aabb_2.size.y &&
			(int)aabb_1.pos.y + aabb_1.size.y > aabb_2.pos.y);
	}
	bool PointInAABB(const Vec2& point, const AABB& aabb)
	{
		return (point.x > aabb.pos.x && point.x < aabb.pos.x + aabb.size.x &&
			point.y > aabb.pos.y && point.y < aabb.pos.y + aabb.size.y);
	}
}