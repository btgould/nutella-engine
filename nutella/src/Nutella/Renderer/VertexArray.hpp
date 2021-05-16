#pragma once

#include "ntpch.hpp"

#include "Nutella/Renderer/VertexBuffer.hpp"
#include "Nutella/Renderer/IndexBuffer.hpp"

namespace Nutella {
	struct VertexBufferAttrib {
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int getTypeSize(unsigned int type);
	};

	class VertexBufferLayout {
	  private:
		std::vector<VertexBufferAttrib> m_vertexAttribs;
		unsigned int m_stride;

	  public:
		VertexBufferLayout() : m_stride(0) {};
		~VertexBufferLayout() {};

		template <unsigned int type>
		inline void push(unsigned int count, unsigned char normalised) {
			m_vertexAttribs.push_back({type, count, normalised});
			m_stride += count * VertexBufferAttrib::getTypeSize(type);
		}

		inline const std::vector<VertexBufferAttrib>& getAttribs() const {
			return m_vertexAttribs;
		}

		inline unsigned int getStride() {
			return m_stride;
		}
	};

	class VertexArray {
	  public:
		VertexArray(VertexBufferLayout& layout, VertexBuffer& vbo, IndexBuffer& ibo);
		~VertexArray();

		void Bind();
		void Unbind();

	  private:
		unsigned int m_RendererID;
	};
} // namespace Nutella
