#include "Platform/OpenGL/OpenGLVertexBuffer.hpp"

#include "glad/glad.h"
#include "Platform/OpenGL/glutil.hpp"

namespace Nutella {
	OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, const unsigned int size) {
		NT_PROFILE_FUNC();

		GL_CALL(glGenBuffers(1, &m_RendererID));
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		NT_PROFILE_FUNC();

		GL_CALL(glDeleteBuffers(1, &m_RendererID));
	}

	void OpenGLVertexBuffer::Bind() const {
		NT_PROFILE_FUNC();

		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}

	void OpenGLVertexBuffer::Unbind() const {
		NT_PROFILE_FUNC();

		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
} // namespace Nutella
