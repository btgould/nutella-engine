#pragma once

#include "Nutella/Renderer/Texture.hpp"

#include "glad/glad.h"

namespace Nutella {
	class OpenGLTexture2D : public Texture2D {
	  public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& filepath);
		virtual ~OpenGLTexture2D();

		virtual void Bind(unsigned int slot = 0) const override;
		virtual void Unbind() const override;

		virtual void Set(void* data, uint32_t size) override;

		virtual void CreateMipmaps() const override;

	  private:
		uint32_t m_RendererID;
		int m_Width, m_Height, m_BPP;

		// dataFormat specifies components of imgData ptr, internalFormat specifies how we would
		// like OpenGL to store the texture
		GLenum m_InternalFormat, m_DataFormat;
	};
} // namespace Nutella
