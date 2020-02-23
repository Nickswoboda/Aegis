#pragma once

#include <glm/glm.hpp>

#include <string>
namespace Aegis {

	class Renderer2D
	{
	public:

		static void Init();

		static void SetClearColor(float r, float g, float b, float a);
		static void Clear();
		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
	};

	class VertexArray
	{
	public:
		VertexArray();

		void Bind();
		void Unbind();

		unsigned int ID_ = 0;
	};

	class Shader
	{
	public:
		Shader(const std::string& file_path);

		void SetMat4(const std::string& name, const glm::mat4& value);
		void SetFloat4(const std::string& name, const glm::vec4& value);
		unsigned int ID_ = 0;

	private:
		void CompileShaders(const std::string& vertex, const std::string& fragment);
	};
}