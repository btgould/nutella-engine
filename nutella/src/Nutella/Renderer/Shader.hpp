#pragma once

#include <string>

namespace Nutella {
	struct ShaderProgramSource {
		std::string vertexSource;
		std::string fragmentSource;
	};

	class Shader {
	  public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind();
		void Unbind();

	  private:
		uint32_t m_RendererID;

		ShaderProgramSource sourceShaders(const std::string& filepath);
		unsigned int compileShader(unsigned int type, const std::string& source);
		unsigned int createShader(const std::string& vertexShader,
								  const std::string& fragmentShader);
	};
} // namespace Nutella
