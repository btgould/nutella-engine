#pragma once

#include <string>

namespace Nutella {
	class Shader {
	  public:
		static Shader* Create(const std::string& filepath);
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};
} // namespace Nutella
