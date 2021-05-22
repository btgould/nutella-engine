#pragma once

#include <string>

#include "glm/glm.hpp"

namespace Nutella {
	class Shader {
	  public:
		static Shader* Create(const std::string& filepath);
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetUniformVec4f(const std::string& name, const glm::vec4& vec) = 0;
		virtual void SetUniformMat4f(const std::string& name, const glm::mat4& mat) = 0;
	};
} // namespace Nutella
