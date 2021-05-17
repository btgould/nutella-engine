#include "Platform/OpenGL/OpenGLVertexBuffer.hpp"

#include "glad/glad.h"
#include "Platform/OpenGL/glutil.hpp"

namespace Nutella {
	OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, const unsigned int size) {
		GL_CALL(glGenBuffers(1, &m_RendererID));
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		GL_CALL(glDeleteBuffers(1, &m_RendererID));
	}

	void OpenGLVertexBuffer::Bind() const {
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}

	void OpenGLVertexBuffer::Unbind() const {
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
} // namespace Nutella
