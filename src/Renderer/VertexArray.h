#pragma once

#include "../Math/Vec2.h"
#include "../Math/Vec3.h"
#include "../Math/Vec4.h"

#include <glm/glm.hpp>
#include <array>

namespace Aegis {

	class VertexArray
	{
	public:
		struct Vertex
		{
			Vec3 position_;
			Vec4 color_;
			Vec2 tex_coords_;
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
		static const std::array<Vec4, 4> vertex_positions_;
	};
}
