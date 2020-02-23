#include "Renderer.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

namespace Aegis {

    static std::unique_ptr<Shader> shader_;
    static std::unique_ptr<VertexArray> vertex_array_;
    static glm::mat4 projection_;

    void Renderer2D::Init()
    {
        shader_ = std::make_unique<Shader>("assets/shaders/Shader.glsl");
        vertex_array_ = std::make_unique<VertexArray>();
        projection_ = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f);
        shader_->SetMat4("u_Projection", projection_);
    }

    void Renderer2D::SetClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void Renderer2D::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

    void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	{
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), { pos.x, pos.y, 0.0f }) * glm::scale(glm::mat4(1.0), { size.x, size.y, 1.0 });
        shader_->SetMat4("u_Transform", transform);
        shader_->SetFloat4("u_Color", color);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}


    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &ID_);
        glBindVertexArray(ID_);

        float vertices[] = {
         1.0f,  1.0f, 0.0f,
         1.0f,  0.0f, 0.0f,
         0.0f,  0.0f, 0.0f,
         0.0f,  1.0f, 0.0f
        };

        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        unsigned int elem_buffer;
        glGenBuffers(1, &elem_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elem_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    }
    void VertexArray::Bind()
    {
        glBindVertexArray(ID_);
    }
    void VertexArray::Unbind()
    {
        glBindVertexArray(ID_);
    }


    Shader::Shader(const std::string& file_path)
    {
        std::ifstream file(file_path);
        std::string shader_source;

        if (file) {
            file.seekg(0, std::ios::end);
            size_t size = file.tellg();
            if (size != -1){
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
                std::cout << "Unable to read shader, possible syntax error.";
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

    void Shader::SetMat4(const std::string& name, const glm::mat4& value)
    {
        GLint location = glGetUniformLocation(ID_, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::SetFloat4(const std::string& name, const glm::vec4& value)
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

        int result1 = 0;
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &result1);
        if (result1 == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertex_shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertex_shader);

            std::cout << "unable to compile shader" << infoLog.data();
        }


        auto fragment_source = fragment.c_str();
        int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
        glCompileShader(fragment_shader);

        int result2 = 0;
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &result2);
        if (result2 == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertex_shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertex_shader);

            std::cout << "unable to compile shader" << infoLog.data();
        }

        ID_ = glCreateProgram();
        glAttachShader(ID_, vertex_shader);
        glAttachShader(ID_, fragment_shader);
        glLinkProgram(ID_);
        glUseProgram(ID_);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }
}