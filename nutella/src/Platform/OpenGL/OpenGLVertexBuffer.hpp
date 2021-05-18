#pragma once

#include "Nutella/Renderer/VertexBuffer.hpp"

namespace Nutella {
	class OpenGLVertexBuffer : public VertexBuffer {
	  public:
		OpenGLVertexBuffer(const void* data, const unsigned int size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

	  private:
		unsigned int m_RendererID;
	};
} // namespace Nutella
