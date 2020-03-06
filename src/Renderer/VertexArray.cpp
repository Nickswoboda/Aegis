#include "VertexArray.h"

#include <glad/glad.h>

#include <array>

namespace Aegis {

    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &ID_);
        glBindVertexArray(ID_);

        float vertices[] = {
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f,  0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.0f, 0.0f, 0.0f, 0.0f,
         0.0f,  1.0f, 0.0f, 0.0f, 1.0f
        };

        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

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
        glBindVertexArray(0);
    }
}