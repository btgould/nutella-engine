#pragma once

#include "Nutella/Renderer/IndexBuffer.hpp"

namespace Nutella {
	class OpenGLIndexBuffer : public IndexBuffer {
	  public:
		OpenGLIndexBuffer(const unsigned int* vertexOrder, const unsigned int size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual unsigned int GetLength() const;

	  private:
		unsigned int m_RendererID;
		unsigned int m_length;
	};
} // namespace Nutella
