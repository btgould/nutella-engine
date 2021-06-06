#pragma once

#include "Nutella/Renderer/Shader.hpp"

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace Nutella {
	using ShaderProgramSource = std::unordered_map<GLenum, std::string>;

	class OpenGLShader : public Shader {
	  public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);

		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetUniform1i(const std::string& name, const int num) override;
		virtual void SetUniformVec2i(const std::string& name, const glm::ivec2& vec) override;
		virtual void SetUniformVec3i(const std::string& name, const glm::ivec3& vec) override;
		virtual void SetUniformVec4i(const std::string& name, const glm::ivec4& vec) override;

		virtual void SetUniform1f(const std::string& name, const float num) override;
		virtual void SetUniformVec2f(const std::string& name, const glm::vec2& vec) override;
		virtual void SetUniformVec3f(const std::string& name, const glm::vec3& vec) override;
		virtual void SetUniformVec4f(const std::string& name, const glm::vec4& vec) override;

		virtual void SetUniformMat3f(const std::string& name, const glm::mat3& mat) override;
		virtual void SetUniformMat4f(const std::string& name, const glm::mat4& mat) override;

	  private:
		uint32_t m_RendererID;

		ShaderProgramSource SourceShaders(const std::string& filepath);
		unsigned int CompileShader(GLenum type, const std::string& source);
		unsigned int CreateShader(ShaderProgramSource sources);

		std::unordered_map<std::string, int> m_UniformLocationCache;

		int GetUniformLocation(const std::string& name);
	};
} // namespace Nutella
