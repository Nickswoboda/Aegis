#include "Interpolation.h"

#include <cmath>

namespace Aegis {
	Vec2 LERP(const Vec2& a, const Vec2& b, float percentage)
	{
		if (percentage >= 1.0f) {
			return b;
		}
		return  a * (1.0f - percentage) + b * percentage;
	}

	Vec2 EaseInQuad(const Vec2& a, const Vec2& b, float percentage)
	{
		if (percentage >= 1.0f) {
			return b;
		}
		float t = percentage * percentage;
		return a * (1.0f - t) + b * t;;
	}
	Vec2 EaseInOutQuad(const Vec2& a, const Vec2& b, float percentage)
	{
		if (percentage >= 1.0f) {
			return b;
		}
		float t = percentage < 0.5 ? 2 * percentage * percentage : 1 - pow(-2 * percentage + 2, 2) / 2;
		return a * (1.0f - t) + b * t;;
	}
	Vec2 EaseInOutQuart(const Vec2& a, const Vec2& b, float percentage)
	{
		if (percentage >= 1.0f) {
			return b;
		}

		float t = percentage < 0.5 ? 8 * percentage * percentage * percentage * percentage : 1 - pow(-2 * percentage + 2, 4) / 2;
		return a * (1.0f - t) + b * t;;
	}
}