#pragma once

namespace Nutella {
	class VertexBuffer {
	  public:
		VertexBuffer(const void* data, const unsigned int size);
		~VertexBuffer();

		void Bind();
		void Unbind();

	  private:
		unsigned int m_RendererID;
	};
} // namespace Nutella
