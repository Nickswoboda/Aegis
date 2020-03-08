#include "VertexArray.h"

#include <glad/glad.h>

#include <array>

namespace Aegis {

    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &ID_);
        glBindVertexArray(ID_);

        glCreateBuffers(1, &vertex_buffer_);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
        glBufferData(GL_ARRAY_BUFFER, max_vertex_count_ * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexArrayAttrib(ID_, 0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position_));

        glEnableVertexArrayAttrib(ID_, 1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color_));

        glEnableVertexArrayAttrib(ID_, 2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, tex_coords_));

        glEnableVertexArrayAttrib(ID_, 3);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texture_ID_));

        uint32_t indices[max_index_count_];
        uint32_t offset = 0;
        for (int i = 0; i < max_index_count_; i += 6) {
            indices[i + 0] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;

            indices[i + 3] = 2 + offset;
            indices[i + 4] = 3 + offset;
            indices[i + 5] = 0 + offset;

            offset += 4;
        }

        glCreateBuffers(1, &index_buffer_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    }
    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &ID_);
        glDeleteBuffers(1, &vertex_buffer_);
        glDeleteBuffers(1, &index_buffer_);
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