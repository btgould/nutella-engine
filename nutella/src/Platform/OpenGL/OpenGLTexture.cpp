#include "OpenGLTexture.hpp"

#include "stb_image.h"

#include "Platform/OpenGL/glutil.hpp"

namespace Nutella {
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height), m_BPP(4) {
		GL_CALL(glGenTextures(1, &m_RendererID));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));

		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

		m_DataFormat = GL_RGBA;
		m_InternalFormat = GL_RGBA8;

		uint8_t imgData[4 * width * height];
		for (int i = 0; i < 4 * width * height; i++) {
			imgData[i] = 0xff;
		}

		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat,
							 GL_UNSIGNED_BYTE, imgData));
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
		: m_Width(0), m_Height(0), m_BPP(0) {
		GL_CALL(glGenTextures(1, &m_RendererID));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));

		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

		stbi_set_flip_vertically_on_load(1); // OpenGL bottom-left is 0, 0
		unsigned char* imgData = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		NT_CORE_ASSERT(imgData, "Failed to load texture!");
		NT_CORE_ASSERT(m_BPP == 3 || m_BPP == 4, "Texture image format not supported!");

		m_DataFormat = (m_BPP == 3) ? GL_RGB : GL_RGBA;
		m_InternalFormat = (m_BPP == 3) ? GL_RGB8 : GL_RGBA8;

		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat,
							 GL_UNSIGNED_BYTE, imgData));

		stbi_image_free(imgData);
	}

	OpenGLTexture2D::~OpenGLTexture2D() { GL_CALL(glDeleteTextures(1, &m_RendererID)); }

	void OpenGLTexture2D::Bind(unsigned int slot /* = 0 */) const {
		GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	}

	void OpenGLTexture2D::Unbind() const { GL_CALL(glBindTexture(GL_TEXTURE_2D, 0)); }

	void OpenGLTexture2D::Set(void* data, uint32_t size) {
		NT_CORE_ASSERT(size == m_Width * m_Height * m_BPP,
					   "Must provide enough data to set entire texture!");

		GL_CALL(glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat,
									GL_UNSIGNED_BYTE, data));
	}

	void OpenGLTexture2D::CreateMipmaps() const {
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
		GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
	}
} // namespace Nutella
