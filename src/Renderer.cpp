#include "Renderer.h"

#include <glad/glad.h>
namespace Aegis {

	void Renderer2D::Init()
	{
        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";

        int vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader_, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertex_shader_);

        int fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader_, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragment_shader_);

        int shader_program_ = glCreateProgram();
        glAttachShader(shader_program_, vertex_shader_);
        glAttachShader(shader_program_, fragment_shader_);
        glLinkProgram(shader_program_);

        glDeleteShader(vertex_shader_);
        glDeleteShader(fragment_shader_);

        float vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f 
        };
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3 
        };

        unsigned int VAO, VBO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
       
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glUseProgram(shader_program_);
	}

	void Renderer2D::Clear(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer2D::DrawQuad(int x_pos, int y_pos, int width, int height)
	{
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}