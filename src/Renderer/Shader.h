#pragma once

#include <glm/glm.hpp>

#include <string>
namespace Aegis {
	class Shader
	{
	public:
		Shader(const std::string& file_path);

		void SetInt(const std::string& name, int value);
		void SetIntVector(const std::string& name, int count, int* values);
		void SetFloat4(const std::string& name, const glm::vec4& value);
		void SetMat4(const std::string& name, const glm::mat4& value);

		void Bind();

		unsigned int ID_ = 0;

	private:
		void CompileShaders(const std::string& vertex, const std::string& fragment);
	};
}