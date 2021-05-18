#include "Platform/OpenGL/OpenGLIndexBuffer.hpp"

#include "glad/glad.h"
#include "Platform/OpenGL/glutil.hpp"

namespace Nutella {
	OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int* vertexOrder, const unsigned int size)
		: m_count(size / sizeof(unsigned int)) {
		GL_CALL(glGenBuffers(1, &m_RendererID));
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
		GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertexOrder, GL_STATIC_DRAW));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		GL_CALL(glDeleteBuffers(1, &m_RendererID));
	}

	void OpenGLIndexBuffer::Bind() const {
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

	void OpenGLIndexBuffer::Unbind() const {
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	unsigned int OpenGLIndexBuffer::GetCount() const {
		return m_count;
	}
} // namespace Nutella
