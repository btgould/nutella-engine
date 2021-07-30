#include "ntpch.hpp"

#include "Platform/OpenGL/OpenGLVertexArray.hpp"

#include "glad/glad.h"
#include "glutil.hpp"

namespace Nutella {
	OpenGLVertexArray::OpenGLVertexArray(const VertexBufferLayout& layout,
										 const Ref<VertexBuffer>& vbo, const Ref<IndexBuffer>& ibo)
		: m_VertexBuffer(vbo), m_IndexBuffer(ibo) {
		NT_PROFILE_FUNC();

		GL_CALL(glCreateVertexArrays(1, &m_RendererID));
		GL_CALL(glBindVertexArray(m_RendererID));
		vbo->Bind();
		ibo->Bind();

		// bind and enable each attribute in desired array
		const auto& attribs = layout.getAttribs();
		unsigned int offset = 0;

		for (int i = 0; i < attribs.size(); i++) {
			const auto& attrib = attribs[i];

			GL_CALL(glEnableVertexAttribArray(i));
			GL_CALL(glVertexAttribPointer(i, attrib.count, getOpenGLType(attrib.type),
										  attrib.normalized ? GL_TRUE : GL_FALSE,
										  layout.getStride(), (void*) offset));
			offset += attrib.count * VertexBufferAttrib::getTypeSize(attrib.type);
		}

		// This is necessary so that creating other primitives (which have to be bound) does not
		// affect the data in this VAO
		GL_CALL(glBindVertexArray(0));
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		NT_PROFILE_FUNC();

		GL_CALL(glDeleteVertexArrays(1, &m_RendererID));
	}

	void OpenGLVertexArray::Bind() const {
		NT_PROFILE_FUNC();

		GL_CALL(glBindVertexArray(m_RendererID));
	}

	void OpenGLVertexArray::Unbind() const {
		NT_PROFILE_FUNC();

		GL_CALL(glBindVertexArray(0));
	}

	const Ref<VertexBuffer>& OpenGLVertexArray::GetVertexBuffer() const { return m_VertexBuffer; }

	const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const { return m_IndexBuffer; }

	unsigned int OpenGLVertexArray::getOpenGLType(VertexAttribType type) {
		switch (type) {
		case VertexAttribType::FLOAT:
			return GL_FLOAT;
			break;
		case VertexAttribType::INT:
			return GL_INT;
			break;
		case VertexAttribType::UINT:
			return GL_UNSIGNED_INT;
			break;

		default:
			NT_CORE_ASSERT(false, "Vertex Attribute type unrecognized!");
			break;
		}

		return 0;
	}
} // namespace Nutella
