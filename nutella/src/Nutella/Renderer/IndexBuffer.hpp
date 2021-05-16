#pragma once

namespace Nutella {
	class IndexBuffer {
	  public:
		IndexBuffer(const unsigned int* vertexOrder, const unsigned int size);
		~IndexBuffer();

		void Bind();
		void Unbind();

	  private:
		unsigned int m_RendererID;
	};
} // namespace Nutella
