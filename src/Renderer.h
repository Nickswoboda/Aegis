#pragma once

namespace Aegis {

	class Renderer2D
	{
	public:
		static void Init();

		static void Clear(float r, float g, float b, float a);
		static void DrawQuad(int x_pos, int y_pos, int width, int height);
	};
}