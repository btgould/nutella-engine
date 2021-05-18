#pragma once

#include "Nutella/Renderer/VertexArray.hpp"

namespace Nutella {
	class OpenGLVertexArray : public VertexArray {
	  public:
		OpenGLVertexArray(const VertexBufferLayout& layout,
						  const std::shared_ptr<VertexBuffer>& vbo,
						  const std::shared_ptr<IndexBuffer>& ibo);
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const override;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;

		static unsigned int getOpenGLType(VertexAttribType type);

	  private:
		unsigned int m_RendererID;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
} // namespace Nutella
