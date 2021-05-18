#pragma once

#include "Nutella/Renderer/IndexBuffer.hpp"

namespace Nutella {
	class OpenGLIndexBuffer : public IndexBuffer {
	  public:
		OpenGLIndexBuffer(const unsigned int* vertexOrder, const unsigned int size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual unsigned int GetCount() const override;

	  private:
		unsigned int m_RendererID;
		unsigned int m_count;
	};
} // namespace Nutella
