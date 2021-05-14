#include "ntpch.hpp"
#include "Nutella/Renderer/Shader.hpp"

#include "glad/glad.h"

namespace Nutella {
	Shader::Shader(std::string& vertexSrc, std::string& fragmentSrc) {
		// create shader object
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// write source code into shader + compile
		const GLchar* glVertexSrc = (const GLchar*) vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &glVertexSrc, NULL);
		glCompileShader(vertexShader);

		// check for compilation failure
		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled != GL_TRUE) {
			GLint errorLen = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &errorLen);

			std::vector<GLchar> errorMsg(errorLen);
			glGetShaderInfoLog(vertexShader, errorLen, &errorLen, &errorMsg[0]);

			glDeleteShader(vertexShader);

			NT_CORE_ERROR("Vertex shader compilation failed!");
			NT_CORE_ERROR("{0}", errorMsg.data());
			NT_CORE_ASSERT(false, "Could not create shader program!");
			return;
		}

		// create shader object
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// write source code into shader + compile
		const GLchar* glFragmentSrc = (const GLchar*) fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &glFragmentSrc, NULL);
		glCompileShader(fragmentShader);

		// check for compilation failure
		isCompiled = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled != GL_TRUE) {
			GLint errorLen = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &errorLen);

			std::vector<GLchar> errorMsg(errorLen);
			glGetShaderInfoLog(fragmentShader, errorLen, &errorLen, &errorMsg[0]);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			NT_CORE_ERROR("Fragment shader compilation failed!");
			NT_CORE_ERROR("{0}", errorMsg.data());
			NT_CORE_ASSERT(false, "Could not create shader program!");
			return;
		}

		// link shaders
		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);
		glLinkProgram(m_RendererID);

		// check for link failure
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);
		if (isLinked != GL_TRUE) {
			GLint errorLen = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &errorLen);

			std::vector<GLchar> errorMsg(errorLen);
			glGetProgramInfoLog(m_RendererID, errorLen, &errorLen, &errorMsg[0]);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			glDeleteProgram(m_RendererID);

			NT_CORE_ERROR("Shader linking failed!");
			NT_CORE_ERROR("{0}", errorMsg.data());
			NT_CORE_ASSERT(false, "Could not create shader program!");
			return;
		}

		// shader creation successful -> detach shaders
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	Shader::~Shader() {
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() {
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() {
		glUseProgram(0);
	}
} // namespace Nutella
