#pragma once

namespace Aegis {
	class VertexArray
	{
	public:
		VertexArray();

		void Bind();
		void Unbind();

		unsigned int ID_ = 0;
	};
}