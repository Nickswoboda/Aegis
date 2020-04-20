#pragma once

#include "Vec2.h"

namespace Aegis
{
	Vec2 LERP(const Vec2& a, const Vec2& b, float percentage);
	Vec2 EaseInQuad(const Vec2& a, const Vec2& b, float percentage);
	Vec2 EaseInOutQuad(const Vec2& a, const Vec2& b, float percentage);
	Vec2 EaseInOutQuart(const Vec2& a, const Vec2& b, float percentage);
}