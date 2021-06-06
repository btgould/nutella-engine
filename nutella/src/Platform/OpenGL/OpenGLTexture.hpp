#pragma once

#include "Nutella/Renderer/Texture.hpp"

namespace Nutella {
	class OpenGLTexture2D : public Texture2D {
	  public:
		OpenGLTexture2D(const std::string& filepath);
		virtual ~OpenGLTexture2D();

		virtual void Bind(unsigned int slot = 0) const override;
		virtual void Unbind() const override;

		virtual void CreateMipmaps() const override;

	  private:
		uint32_t m_RendererID;
		int m_Width, m_Height, m_BPP;
	};
} // namespace Nutella
