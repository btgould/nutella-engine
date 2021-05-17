#pragma once

namespace Nutella {
	class VertexBuffer {
	  public:
		static VertexBuffer* Create(const void* data, const unsigned int size);
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};
} // namespace Nutella
