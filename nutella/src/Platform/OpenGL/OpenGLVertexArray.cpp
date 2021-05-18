#include "ntpch.hpp"

#include "Platform/OpenGL/OpenGLVertexArray.hpp"

#include "glad/glad.h"
#include "glutil.hpp"

namespace Nutella {
	OpenGLVertexArray::OpenGLVertexArray(const VertexBufferLayout& layout,
										 const std::shared_ptr<VertexBuffer>& vbo,
										 const std::shared_ptr<IndexBuffer>& ibo)
		: m_VertexBuffer(vbo), m_IndexBuffer(ibo) {
		GL_CALL(glCreateVertexArrays(1, &m_RendererID));
		this->Bind();
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
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		GL_CALL(glDeleteVertexArrays(1, &m_RendererID))
	}

	void OpenGLVertexArray::Bind() const {
		GL_CALL(glBindVertexArray(m_RendererID));
	}

	void OpenGLVertexArray::Unbind() const {
		GL_CALL(glBindVertexArray(m_RendererID));
	}

	const std::shared_ptr<VertexBuffer>& OpenGLVertexArray::GetVertexBuffer() const {
		return m_VertexBuffer;
	}

	const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const {
		return m_IndexBuffer;
	}

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
