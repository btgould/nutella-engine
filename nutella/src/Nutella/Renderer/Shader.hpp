#pragma once

#include <string>

#include "glm/glm.hpp"

namespace Nutella {
	class Shader {
	  public:
		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetUniform1i(const std::string& name, const int num) = 0;
		virtual void SetUniformVec2i(const std::string& name, const glm::ivec2& vec) = 0;
		virtual void SetUniformVec3i(const std::string& name, const glm::ivec3& vec) = 0;
		virtual void SetUniformVec4i(const std::string& name, const glm::ivec4& vec) = 0;

		virtual void SetUniform1f(const std::string& name, const float num) = 0;
		virtual void SetUniformVec2f(const std::string& name, const glm::vec2& vec) = 0;
		virtual void SetUniformVec3f(const std::string& name, const glm::vec3& vec) = 0;
		virtual void SetUniformVec4f(const std::string& name, const glm::vec4& vec) = 0;

		virtual void SetUniformMat3f(const std::string& name, const glm::mat3& mat) = 0;
		virtual void SetUniformMat4f(const std::string& name, const glm::mat4& mat) = 0;
	};
} // namespace Nutella
