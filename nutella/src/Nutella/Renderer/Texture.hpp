#pragma once

#include <string>

namespace Nutella {
	enum class TexWrapType { NONE, REPEAT, MIRRORED_REPEAT, CLAMP };
	enum class TexMinFilter { NEAREST, LERP, MIPMAP_NEAREST, MIPMAP_LERP };
	enum class TexMagFilter { NEAREST, LERP };

	class Texture {
	  public:
		virtual ~Texture() {};

		virtual void Bind(unsigned int slot = 0) const = 0;
		virtual void Unbind() const = 0;

		virtual void Set(void* data, uint32_t size) = 0;

		virtual void CreateMipmaps() const = 0;
	};

	class Texture2D : public Texture {
	  public:
		static Ref<Texture> Create(uint32_t width, uint32_t height,
								   TexWrapType wrapType = TexWrapType::REPEAT,
								   TexMinFilter minFilter = TexMinFilter::NEAREST,
								   TexMagFilter magFilter = TexMagFilter::NEAREST);
		static Ref<Texture> Create(const std::string& filepath,
								   TexWrapType wrapType = TexWrapType::REPEAT,
								   TexMinFilter minFilter = TexMinFilter::NEAREST,
								   TexMagFilter magFilter = TexMagFilter::NEAREST);
	};
} // namespace Nutella
