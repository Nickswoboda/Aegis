#pragma once

#include <glm/glm.hpp>
namespace Aegis {

	class VertexArray
	{
	public:
		struct Vertex
		{
			glm::vec3 position_;
			glm::vec4 color_;
			glm::vec2 tex_coords_;
			float texture_ID_;
		};
		VertexArray();
		~VertexArray();
		void Bind();
		void Unbind();

		unsigned int ID_ = 0;
		unsigned int vertex_buffer_ = 0;
		unsigned int index_buffer_ = 0;

		static const size_t max_quad_count_ = 1000;
		static const size_t max_vertex_count_ = max_quad_count_ * 4;
		static constexpr size_t max_index_count_ = max_quad_count_ * 6;
	};
}