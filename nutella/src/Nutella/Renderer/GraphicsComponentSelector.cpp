#include "ntpch.hpp"

#include "Nutella/Renderer/Renderer.hpp"
#include "Nutella/Renderer/VertexBuffer.hpp"
#include "Nutella/Renderer/IndexBuffer.hpp"
#include "Nutella/Renderer/VertexArray.hpp"
#include "Nutella/Renderer/Shader.hpp"
#include "Nutella/Renderer/Texture.hpp"

#include "Platform/OpenGL/OpenGLVertexBuffer.hpp"
#include "Platform/OpenGL/OpenGLIndexBuffer.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"
#include "Platform/OpenGL/OpenGLTexture.hpp"

namespace Nutella {

	Ref<VertexBuffer> VertexBuffer::Create(const void* data, const unsigned int size) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::NONE:
			NT_CORE_ASSERT(false, "No render API selected!");
			return nullptr;
			break;
		case RendererAPI::API::OPEN_GL:
			return CreateRef<OpenGLVertexBuffer>(data, size);
			break;
		default:
			NT_CORE_ASSERT(false, "Unrecognized render API selected!");
			return nullptr;
			break;
		}
	}

	Ref<IndexBuffer> IndexBuffer::Create(const unsigned int* vertexOrder, const unsigned int size) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::NONE:
			NT_CORE_ASSERT(false, "No render API selected!");
			return nullptr;
			break;
		case RendererAPI::API::OPEN_GL:
			return CreateRef<OpenGLIndexBuffer>(vertexOrder, size);
			break;
		default:
			NT_CORE_ASSERT(false, "Unrecognized render API selected!");
			return nullptr;
			break;
		}
	}

	Ref<VertexArray> VertexArray::Create(const VertexBufferLayout& layout,
										 const Ref<VertexBuffer>& vbo,
										 const Ref<IndexBuffer>& ibo) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::NONE:
			NT_CORE_ASSERT(false, "No render API selected!");
			return nullptr;
			break;
		case RendererAPI::API::OPEN_GL:
			return CreateRef<OpenGLVertexArray>(layout, vbo, ibo);
			break;
		default:
			NT_CORE_ASSERT(false, "Unrecognized render API selected!");
			return nullptr;
			break;
		}
	}

	Ref<Shader> Shader::Create(const std::string& filepath) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::NONE:
			NT_CORE_ASSERT(false, "No render API selected!");
			return nullptr;
			break;
		case RendererAPI::API::OPEN_GL:
			return CreateRef<OpenGLShader>(filepath);
			break;
		default:
			NT_CORE_ASSERT(false, "Unrecognized render API selected!");
			return nullptr;
			break;
		}
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc,
							   const std::string& fragmentSrc) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::NONE:
			NT_CORE_ASSERT(false, "No render API selected!");
			return nullptr;
			break;
		case RendererAPI::API::OPEN_GL:
			return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
			break;
		default:
			NT_CORE_ASSERT(false, "Unrecognized render API selected!");
			return nullptr;
			break;
		}
	}

	Ref<Texture> Texture2D::Create(uint32_t width, uint32_t height) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::NONE:
			NT_CORE_ASSERT(false, "No render API selected!");
			return nullptr;
			break;
		case RendererAPI::API::OPEN_GL:
			return CreateRef<OpenGLTexture2D>(width, height);
			break;
		default:
			NT_CORE_ASSERT(false, "Unrecognized render API selected!");
			return nullptr;
			break;
		}
	}

	Ref<Texture> Texture2D::Create(const std::string& filepath) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::NONE:
			NT_CORE_ASSERT(false, "No render API selected!");
			return nullptr;
			break;
		case RendererAPI::API::OPEN_GL:
			return CreateRef<OpenGLTexture2D>(filepath);
			break;
		default:
			NT_CORE_ASSERT(false, "Unrecognized render API selected!");
			return nullptr;
			break;
		}
	}

} // namespace Nutella
