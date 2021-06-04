#pragma once

#include "Nutella/Renderer/VertexArray.hpp"

namespace Nutella {
	class OpenGLVertexArray : public VertexArray {
	  public:
		OpenGLVertexArray(const VertexBufferLayout& layout, const Ref<VertexBuffer>& vbo,
						  const Ref<IndexBuffer>& ibo);
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const Ref<VertexBuffer>& GetVertexBuffer() const override;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override;

		static unsigned int getOpenGLType(VertexAttribType type);

	  private:
		unsigned int m_RendererID;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
} // namespace Nutella
