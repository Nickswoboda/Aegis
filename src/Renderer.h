#pragma once

namespace Aegis {

	class Renderer2D
	{
	public:
		static void Init();

		static void SetClearColor(float r, float g, float b, float a);
		static void Clear();
		static void DrawQuad(int x_pos, int y_pos, int width, int height);
	};

	class VertexArray
	{
	public:
		VertexArray();

		void Bind();
		void Unbind();

		unsigned int ID_;
	};
}