#include "ntpch.hpp"

#include "Nutella/Renderer/Renderer.hpp"
#include "Nutella/Renderer/VertexBuffer.hpp"
#include "Nutella/Renderer/IndexBuffer.hpp"
#include "Nutella/Renderer/Shader.hpp"

#include "Platform/OpenGL/OpenGLVertexBuffer.hpp"
#include "Platform/OpenGL/OpenGLIndexBuffer.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

namespace Nutella {

	VertexBuffer* VertexBuffer::Create(const void* data, const unsigned int size) {
		switch (Renderer::getAPI()) {
		case RenderAPI::NONE:
			NT_CORE_ASSERT(false, "No render API selected!");
			return nullptr;
			break;
		case RenderAPI::OPEN_GL:
			return new OpenGLVertexBuffer(data, size);
			break;
		default:
			NT_CORE_ASSERT(false, "Unrecognized render API selected!");
			return nullptr;
			break;
		}
	}

	IndexBuffer* IndexBuffer::Create(const unsigned int* vertexOrder, const unsigned int size) {
		switch (Renderer::getAPI()) {
		case RenderAPI::NONE:
			NT_CORE_ASSERT(false, "No render API selected!");
			return nullptr;
			break;
		case RenderAPI::OPEN_GL:
			return new OpenGLIndexBuffer(vertexOrder, size);
			break;
		default:
			NT_CORE_ASSERT(false, "Unrecognized render API selected!");
			return nullptr;
			break;
		}
	}

	Shader* Shader::Create(const std::string& filepath) {
		switch (Renderer::getAPI()) {
		case RenderAPI::NONE:
			NT_CORE_ASSERT(false, "No render API selected!");
			return nullptr;
			break;
		case RenderAPI::OPEN_GL:
			return new OpenGLShader(filepath);
			break;
		default:
			NT_CORE_ASSERT(false, "Unrecognized render API selected!");
			return nullptr;
			break;
		}
	}

} // namespace Nutella
