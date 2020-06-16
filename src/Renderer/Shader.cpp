#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

namespace Aegis{
    Shader::Shader(const std::string& file_path)
    {
        std::ifstream file(file_path);
        std::string shader_source;

        if (file) {
            file.seekg(0, std::ios::end);
            size_t size = file.tellg();
            if (size != -1) {
                shader_source.resize(size);
                file.seekg(0, std::ios::beg);
                file.read(&shader_source[0], size);
            }
        }
        else {
            std::cout << "Unable to open shader file\n";
        }

        std::string vertex_shader;
        std::string fragment_shader;

        std::string token("#type");
        auto token_size = token.size();

        auto pos = shader_source.find(token);

        while (pos != std::string::npos) {

            auto eol = shader_source.find('\n', pos);
            std::string type = shader_source.substr(pos + token_size + 1, eol - (pos + token_size + 1));
            if (type != "vertex" && type != "fragment") {
                std::cout << "Unable to read shader, possible syntax error.\n";
                return;
            }
            else {
                auto shader_start = shader_source.find_first_not_of('\n', eol);
                pos = shader_source.find("#type", eol);

                if (type == "vertex") {
                    vertex_shader = shader_source.substr(shader_start, pos - shader_start);
                }
                else {
                    fragment_shader = shader_source.substr(shader_start, pos - shader_start);
                }
            }
        }

        CompileShaders(vertex_shader, fragment_shader);
    }

	Shader::Shader(const std::string& vertex_shader, const std::string& fragment_shader)
	{
			CompileShaders(vertex_shader, fragment_shader);
	}
    void Shader::SetMat4(const std::string& name, const glm::mat4& value)
    {
        GLint location = glGetUniformLocation(ID_, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::Bind()
    {
        glUseProgram(ID_);
    }

    void Shader::SetInt(const std::string& name, int value)
    {
        GLint location = glGetUniformLocation(ID_, name.c_str());
        glUniform1i(location, value);
    }

    void Shader::SetIntVector(const std::string& name, int count, int* values)
    {
        GLint location = glGetUniformLocation(ID_, name.c_str());
        glUniform1iv(location, count, values);
    }

    void Shader::SetFloat4(const std::string& name, const Vec4& value)
    {
        GLint location = glGetUniformLocation(ID_, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void Shader::CompileShaders(const std::string& vertex, const std::string& fragment)
    {
        int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        auto vertex_source = vertex.c_str();
        glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
        glCompileShader(vertex_shader);

        int result = 0;
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertex_shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertex_shader);

            std::cout << "unable to compile vertex shader:" << infoLog.data();
        }


        int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        auto fragment_source = fragment.c_str();
        glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
        glCompileShader(fragment_shader);

        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragment_shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(fragment_shader);

            std::cout << "unable to compile fragment shader:" << infoLog.data();
        }

        ID_ = glCreateProgram();
        glAttachShader(ID_, vertex_shader);
        glAttachShader(ID_, fragment_shader);
        glLinkProgram(ID_);

        GLint isLinked = 0;
        glGetProgramiv(ID_, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(ID_, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(ID_, maxLength, &maxLength, &infoLog[0]);

            std::cout << "unable to link shader." << infoLog.data() << "\n";
            return;
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }
}
