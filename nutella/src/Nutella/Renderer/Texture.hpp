#pragma once

#include <string>

namespace Nutella {
	class Texture {
	  public:
		static Texture* Create(const std::string& filepath);
		virtual ~Texture() {};

		virtual void Bind(unsigned int slot = 0) const = 0;
		virtual void Unbind() const = 0;

		virtual void CreateMipmaps() const = 0;
	};
} // namespace Nutella
