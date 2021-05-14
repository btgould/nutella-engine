#include "ntpch.hpp"
#include "Nutella/Renderer/Shader.hpp"

#include "glad/glad.h"
#include "Platform/OpenGL/glutil.hpp"

namespace Nutella {
	Shader::Shader(std::string& vertexSrc, std::string& fragmentSrc) {
		// create shader object
		GL_CALL(GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER));

		// write source code into shader + compile
		const GLchar* glVertexSrc = (const GLchar*) vertexSrc.c_str();
		GL_CALL(glShaderSource(vertexShader, 1, &glVertexSrc, NULL));
		GL_CALL(glCompileShader(vertexShader));

		// check for compilation failure
		GLint isCompiled = 0;
		GL_CALL(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled));
		if (isCompiled != GL_TRUE) {
			GLint errorLen = 0;
			GL_CALL(glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &errorLen));

			std::vector<GLchar> errorMsg(errorLen);
			GL_CALL(glGetShaderInfoLog(vertexShader, errorLen, &errorLen, &errorMsg[0]));

			GL_CALL(glDeleteShader(vertexShader));

			NT_CORE_ERROR("Vertex shader compilation failed!");
			NT_CORE_ERROR("{0}", errorMsg.data());
			NT_CORE_ASSERT(false, "Could not create shader program!");
			return;
		}

		// create shader object
		GL_CALL(GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));

		// write source code into shader + compile
		const GLchar* glFragmentSrc = (const GLchar*) fragmentSrc.c_str();
		GL_CALL(glShaderSource(fragmentShader, 1, &glFragmentSrc, NULL));
		GL_CALL(glCompileShader(fragmentShader));

		// check for compilation failure
		isCompiled = 0;
		GL_CALL(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled));
		if (isCompiled != GL_TRUE) {
			GLint errorLen = 0;
			GL_CALL(glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &errorLen));

			std::vector<GLchar> errorMsg(errorLen);
			GL_CALL(glGetShaderInfoLog(fragmentShader, errorLen, &errorLen, &errorMsg[0]));

			GL_CALL(glDeleteShader(vertexShader));
			GL_CALL(glDeleteShader(fragmentShader));

			NT_CORE_ERROR("Fragment shader compilation failed!");
			NT_CORE_ERROR("{0}", errorMsg.data());
			NT_CORE_ASSERT(false, "Could not create shader program!");
			return;
		}

		// link shaders
		m_RendererID = glCreateProgram();
		GL_CALL(glAttachShader(m_RendererID, 42));
		GL_CALL(glAttachShader(m_RendererID, fragmentShader));
		GL_CALL(glLinkProgram(m_RendererID));

		// check for link failure
		GLint isLinked = 0;
		GL_CALL(glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked));
		if (isLinked != GL_TRUE) {
			GLint errorLen = 0;
			GL_CALL(glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &errorLen));

			std::vector<GLchar> errorMsg(errorLen);
			GL_CALL(glGetProgramInfoLog(m_RendererID, errorLen, &errorLen, &errorMsg[0]));

			GL_CALL(glDeleteShader(vertexShader));
			GL_CALL(glDeleteShader(fragmentShader));
			GL_CALL(glDeleteProgram(m_RendererID));

			NT_CORE_ERROR("Shader linking failed!");
			NT_CORE_ERROR("{0}", errorMsg.data());
			NT_CORE_ASSERT(false, "Could not create shader program!");
			return;
		}

		// shader creation successful -> detach shaders
		GL_CALL(glDetachShader(m_RendererID, vertexShader));
		GL_CALL(glDetachShader(m_RendererID, fragmentShader));
	}

	Shader::~Shader() {
		GL_CALL(glDeleteProgram(m_RendererID));
	}

	void Shader::Bind() {
		GL_CALL(glUseProgram(m_RendererID));
	}

	void Shader::Unbind() {
		GL_CALL(glUseProgram(0));
	}
} // namespace Nutella
