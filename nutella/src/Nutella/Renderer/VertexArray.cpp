#include "Nutella/Renderer/VertexArray.hpp"

#include "Platform/OpenGL/glutil.hpp"

namespace Nutella {
	unsigned int VertexBufferAttrib::getTypeSize(GLenum type) {
		switch (type) {
		case GL_FLOAT:
			return sizeof(float);
			break;
		case GL_UNSIGNED_INT:
			return sizeof(unsigned int);
			break;
		case GL_UNSIGNED_BYTE:
			return sizeof(unsigned char);
			break;
		default:
			NT_CORE_ASSERT(false, "Invalid Vertex Attrib Type!");
			break;
		}

		return 0;
	}

	VertexArray::VertexArray(VertexBufferLayout& layout, VertexBuffer& vbo, IndexBuffer& ibo) {
		GL_CALL(glCreateVertexArrays(1, &m_RendererID));
		this->Bind();
		vbo.Bind();
		ibo.Bind();

		// bind and enable each attribute in desired array
		const auto& attribs = layout.getAttribs();
		unsigned int offset = 0;

		for (int i = 0; i < attribs.size(); i++) {
			const auto& attrib = attribs[i];

			GL_CALL(glEnableVertexAttribArray(i));
			GL_CALL(glVertexAttribPointer(i, attrib.count, attrib.type, attrib.normalized,
										  layout.getStride(), (void*) offset));
			offset += attrib.count * VertexBufferAttrib::getTypeSize(attrib.type);
		}
	}

	VertexArray::~VertexArray() {
		GL_CALL(glDeleteVertexArrays(1, &m_RendererID))
	}

	void VertexArray::Bind() {
		GL_CALL(glBindVertexArray(m_RendererID));
	}

	void VertexArray::Unbind() {
		GL_CALL(glBindVertexArray(0));
	}
} // namespace Nutella
