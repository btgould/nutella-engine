#include "OpenGLTexture.hpp"

#include "stb_image.h"

#include "glad/glad.h"
#include "Platform/OpenGL/glutil.hpp"

namespace Nutella {
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

		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA,
							 GL_UNSIGNED_BYTE, imgData));

		stbi_image_free(imgData);
	}

	OpenGLTexture2D::~OpenGLTexture2D() { GL_CALL(glDeleteTextures(1, &m_RendererID)); }

	void OpenGLTexture2D::Bind(unsigned int slot /* = 0 */) const {
		GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	}

	void OpenGLTexture2D::Unbind() const { GL_CALL(glBindTexture(GL_TEXTURE_2D, 0)); }

	void OpenGLTexture2D::CreateMipmaps() const {
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
		GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
	}
} // namespace Nutella
