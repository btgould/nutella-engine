#pragma once

#include "Nutella/Renderer/Shader.hpp"

#include "glm/glm.hpp"

namespace Nutella {
	struct ShaderProgramSource {
		std::string vertexSource;
		std::string fragmentSource;
	};

	class OpenGLShader : public Shader {
	  public:
		OpenGLShader(const std::string& filepath);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetUniform1i(const std::string& name, const int num) override;
		virtual void SetUniformVec4f(const std::string& name, const glm::vec4& vec) override;
		virtual void SetUniformMat4f(const std::string& name, const glm::mat4& mat) override;

	  private:
		uint32_t m_RendererID;

		ShaderProgramSource sourceShaders(const std::string& filepath);
		unsigned int compileShader(unsigned int type, const std::string& source);
		unsigned int createShader(const std::string& vertexShader,
								  const std::string& fragmentShader);

		std::unordered_map<std::string, int> m_UniformLocationCache;

		int GetUniformLocation(const std::string& name);
	};
} // namespace Nutella
