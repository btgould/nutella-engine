#pragma once

namespace Nutella {
	class IndexBuffer {
	  public:
		static IndexBuffer* Create(const unsigned int* vertexOrder, const unsigned int size);
		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual unsigned int GetCount() const = 0;
	};
} // namespace Nutella
