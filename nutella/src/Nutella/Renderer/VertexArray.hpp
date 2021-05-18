#pragma once

#include "ntpch.hpp"

#include "Nutella/Renderer/VertexBuffer.hpp"
#include "Nutella/Renderer/IndexBuffer.hpp"

namespace Nutella {

	enum class VertexAttribType { NONE = 0, FLOAT, INT, UINT };

	struct VertexBufferAttrib {
		VertexAttribType type;
		unsigned int count;
		bool normalized;

		inline static size_t getTypeSize(VertexAttribType type) {
			switch (type) {
			case VertexAttribType::FLOAT:
				return sizeof(float);
				break;
			case VertexAttribType::INT:
				return sizeof(int);
				break;
			case VertexAttribType::UINT:
				return sizeof(unsigned int);
				break;

			default:
				NT_CORE_ASSERT(false, "Vertex Attribute type unrecognized!");
				break;
			}

			return 0;
		};
	};

	class VertexBufferLayout {
	  private:
		std::vector<VertexBufferAttrib> m_vertexAttribs;
		unsigned int m_stride;

	  public:
		VertexBufferLayout() : m_stride(0) {};
		~VertexBufferLayout() {};

		inline void push(VertexAttribType type, unsigned int count, bool normalised) {
			m_vertexAttribs.push_back({type, count, normalised});
			m_stride += count * VertexBufferAttrib::getTypeSize(type);
		}

		inline const std::vector<VertexBufferAttrib>& getAttribs() const {
			return m_vertexAttribs;
		}

		inline unsigned int getStride() const {
			return m_stride;
		}
	};

	class VertexArray {
	  public:
		static VertexArray* Create(const VertexBufferLayout& layout,
								   const std::shared_ptr<VertexBuffer>& vbo,
								   const std::shared_ptr<IndexBuffer>& ibo);
		virtual ~VertexArray() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;
	};
} // namespace Nutella
