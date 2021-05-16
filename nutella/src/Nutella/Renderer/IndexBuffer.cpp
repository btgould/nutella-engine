#include "Nutella/Renderer/IndexBuffer.hpp"

#include "glad/glad.h"
#include "Platform/OpenGL/glutil.hpp"

namespace Nutella {
	IndexBuffer::IndexBuffer(const unsigned int* vertexOrder, const unsigned int size) {
		GL_CALL(glGenBuffers(1, &m_RendererID));
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
		GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertexOrder, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer() {
		GL_CALL(glDeleteBuffers(1, &m_RendererID));
	}

	void IndexBuffer::Bind() {
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

	void IndexBuffer::Unbind() {
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
} // namespace Nutella
