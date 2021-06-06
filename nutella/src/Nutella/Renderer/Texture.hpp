#pragma once

#include <string>

namespace Nutella {
	class Texture {
	  public:
		virtual ~Texture() {};

		virtual void Bind(unsigned int slot = 0) const = 0;
		virtual void Unbind() const = 0;

		virtual void CreateMipmaps() const = 0;
	};

	class Texture2D : public Texture {
	  public:
		static Ref<Texture> Create(const std::string& filepath);
	};
} // namespace Nutella
