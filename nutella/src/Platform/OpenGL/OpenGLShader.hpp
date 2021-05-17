#pragma once

#include "Nutella/Renderer/Shader.hpp"

namespace Nutella {
	struct ShaderProgramSource {
		std::string vertexSource;
		std::string fragmentSource;
	};

	class OpenGLShader : public Shader {
	  public:
		OpenGLShader(const std::string& filepath);
		virtual ~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;

	  private:
		uint32_t m_RendererID;

		ShaderProgramSource sourceShaders(const std::string& filepath);
		unsigned int compileShader(unsigned int type, const std::string& source);
		unsigned int createShader(const std::string& vertexShader,
								  const std::string& fragmentShader);
	};
} // namespace Nutella
