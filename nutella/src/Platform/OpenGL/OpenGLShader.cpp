#include "ntpch.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

#include "glad/glad.h"
#include "Platform/OpenGL/glutil.hpp"

#include <fstream>

namespace Nutella {
	OpenGLShader::OpenGLShader(const std::string& filepath) {
		ShaderProgramSource source = sourceShaders(filepath);
		m_RendererID = createShader(source.vertexSource, source.fragmentSource);
	}

	OpenGLShader::~OpenGLShader() { GL_CALL(glDeleteProgram(m_RendererID)); }

	void OpenGLShader::Bind() const { GL_CALL(glUseProgram(m_RendererID)); }

	void OpenGLShader::Unbind() const { GL_CALL(glUseProgram(0)); }

	void OpenGLShader::SetUniformVec4f(const std::string& name, const glm::vec4& vec) {
		GL_CALL(glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w));
	}

	void OpenGLShader::SetUniformMat4f(const std::string& name, const glm::mat4& mat) {
		GL_CALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
	}

	ShaderProgramSource OpenGLShader::sourceShaders(const std::string& filepath) {
		std::stringstream source[2];
		std::ifstream file(filepath);

		enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
		ShaderType type = ShaderType::NONE;

		std::string line;
		while (getline(file, line)) {
			if (line.find("#shader") != std::string::npos) {
				// declaration of a shader -> find type
				if (line.find("vertex") != std::string::npos) {
					type = ShaderType::VERTEX;
				} else if (line.find("fragment") != std::string::npos) {
					type = ShaderType::FRAGMENT;
				}
			} else {
				// add line to current shader code
				source[(int) type] << line << "\n";
			}
		}

		return {source[0].str(), source[1].str()};
	}

	unsigned int OpenGLShader::compileShader(unsigned int type, const std::string& source) {
		// create + compile shader
		GL_CALL(unsigned int id = glCreateShader(type));
		const char* const src = source.c_str();
		GL_CALL(glShaderSource(id, 1, &src, nullptr));
		GL_CALL(glCompileShader(id));

		// check for compilation errors
		GLint isCompiled = 0;
		GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled));
		if (isCompiled != GL_TRUE) {
			GLint errorLen = 0;
			GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &errorLen));

			std::vector<GLchar> errorMsg(errorLen);
			GL_CALL(glGetShaderInfoLog(id, errorLen, &errorLen, &errorMsg[0]));

			GL_CALL(glDeleteShader(id));

			NT_CORE_ERROR("{0} shader compilation failed!",
						  (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment");
			NT_CORE_ERROR("{0}", errorMsg.data());
			NT_CORE_ASSERT(false, "Could not create shader program!");
		}

		return id;
	}

	unsigned int OpenGLShader::createShader(const std::string& vertexShader,
											const std::string& fragmentShader) {
		GL_CALL(unsigned int id = glCreateProgram());

		unsigned int vertexShaderID = compileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fragmentShaderID = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
		GL_CALL(glAttachShader(id, vertexShaderID));
		GL_CALL(glAttachShader(id, fragmentShaderID));

		GL_CALL(glLinkProgram(id));

		// check for linking errors
		GLint isLinked = 0;
		GL_CALL(glGetProgramiv(id, GL_LINK_STATUS, &isLinked));
		if (isLinked != GL_TRUE) {
			GLint errorLen = 0;
			GL_CALL(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &errorLen));

			std::vector<GLchar> errorMsg(errorLen);
			GL_CALL(glGetProgramInfoLog(id, errorLen, &errorLen, &errorMsg[0]));

			GL_CALL(glDeleteShader(vertexShaderID));
			GL_CALL(glDeleteShader(fragmentShaderID));
			GL_CALL(glDeleteProgram(id));

			NT_CORE_ERROR("Shader linking failed!");
			NT_CORE_ERROR("{0}", errorMsg.data());
			NT_CORE_ASSERT(false, "Could not create shader program!");
		}

		// shader creation successful -> detach shaders
		GL_CALL(glDetachShader(id, vertexShaderID));
		GL_CALL(glDetachShader(id, fragmentShaderID));

		return id;
	}

	int OpenGLShader::GetUniformLocation(const std::string& name) {
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		GL_CALL(int location = glGetUniformLocation(m_RendererID, name.c_str()));

		if (location == -1)
			NT_CORE_WARN("Uniform {0} not found!", name);

		m_UniformLocationCache[name] = location;
		return location;
	}
} // namespace Nutella
