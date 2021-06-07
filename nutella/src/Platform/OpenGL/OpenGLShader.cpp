#include "ntpch.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

#include "Platform/OpenGL/glutil.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <fstream>
#include <filesystem>

namespace Nutella {
	OpenGLShader::OpenGLShader(const std::string& filepath) {
		ShaderProgramSource source = SourceShaders(filepath);
		m_RendererID = CreateShader(source);

		std::filesystem::path path = filepath;
		m_Name = path.stem().string();
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc,
							   const std::string& fragmentSrc)
		: m_Name(name) {
		ShaderProgramSource source;
		source[GL_VERTEX_SHADER] = vertexSrc;
		source[GL_FRAGMENT_SHADER] = fragmentSrc;
		m_RendererID = CreateShader(source);
	}

	OpenGLShader::~OpenGLShader() { GL_CALL(glDeleteProgram(m_RendererID)); }

	void OpenGLShader::Bind() const { GL_CALL(glUseProgram(m_RendererID)); }

	void OpenGLShader::Unbind() const { GL_CALL(glUseProgram(0)); }

	const std::string& OpenGLShader::GetName() const { return m_Name; }

	// Utility functions to create shaders
	// -----------------------------------------------------------------------
	GLenum GetShaderTypeFromKeyword(const std::string& keyword) {
		if (keyword == "vertex")
			return GL_VERTEX_SHADER;
		if (keyword == "fragment" || keyword == "pixel")
			return GL_FRAGMENT_SHADER;

		NT_CORE_ASSERT(false, " Unrecognized / Unsupported shader type!");
		return 0;
	}

	ShaderProgramSource OpenGLShader::SourceShaders(const std::string& filepath) {
		const char* declKeyword = "#shader";
		unsigned int declKeywordLen = strlen(declKeyword);

		ShaderProgramSource sources;
		std::ifstream file(filepath);

		std::string line;
		std::stringstream currShaderSource;
		GLenum currShaderType;
		unsigned int currShaderStart;

		while (getline(file, line)) {
			if (line.find(declKeyword) != std::string::npos) {
				currShaderStart = line.find(declKeyword);
				// declaration of a new shader
				if (!currShaderSource.str().empty()) {
					// push old shader code if it exists
					sources[currShaderType] = currShaderSource.str();
					currShaderSource.str("");
				}

				// update new shader type
				std::string shaderKeyword = line.substr(currShaderStart + declKeywordLen + 1);
				currShaderType = GetShaderTypeFromKeyword(shaderKeyword);
			} else {
				// add line to current shader code
				currShaderSource << line << "\n";
			}
		}

		// push last shader code
		sources[currShaderType] = currShaderSource.str();

		file.close();
		return sources;
	}

	unsigned int OpenGLShader::CompileShader(GLenum type, const std::string& source) {
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

			NT_CORE_ERROR("Shader compilation failed!");
			NT_CORE_ERROR("{0}", errorMsg.data());
			NT_CORE_ASSERT(false, "Could not create shader program!");
		}

		return id;
	}

	unsigned int OpenGLShader::CreateShader(ShaderProgramSource sources) {
		GL_CALL(unsigned int id = glCreateProgram());
		std::vector<unsigned int> shaderProgramIDs;
		shaderProgramIDs.reserve(sources.size());

		for (auto& [type, source] : sources) {
			unsigned int shaderID = CompileShader(type, source);
			GL_CALL(glAttachShader(id, shaderID));
			shaderProgramIDs.push_back(shaderID);
		}

		GL_CALL(glLinkProgram(id));

		// check for linking errors
		GLint isLinked = 0;
		GL_CALL(glGetProgramiv(id, GL_LINK_STATUS, &isLinked));
		if (isLinked != GL_TRUE) {
			GLint errorLen = 0;
			GL_CALL(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &errorLen));

			std::vector<GLchar> errorMsg(errorLen);
			GL_CALL(glGetProgramInfoLog(id, errorLen, &errorLen, &errorMsg[0]));

			for (unsigned int shaderID : shaderProgramIDs) {
				GL_CALL(glDeleteShader(shaderID));
			}

			GL_CALL(glDeleteProgram(id));

			NT_CORE_ERROR("Shader linking failed!");
			NT_CORE_ERROR("{0}", errorMsg.data());
			NT_CORE_ASSERT(false, "Could not create shader program!");
		}

		// shader creation successful -> detach shaders
		for (unsigned int shaderID : shaderProgramIDs) {
			GL_CALL(glDetachShader(id, shaderID));
		}

		return id;
	}

	// Uniform set functions
	// -----------------------------------------------------------------------
	void OpenGLShader::SetUniform1i(const std::string& name, const int num) {
		GL_CALL(glUniform1i(GetUniformLocation(name), num));
	}

	void OpenGLShader::SetUniformVec2i(const std::string& name, const glm::ivec2& vec) {
		GL_CALL(glUniform2i(GetUniformLocation(name), vec.x, vec.y));
	}

	void OpenGLShader::SetUniformVec3i(const std::string& name, const glm::ivec3& vec) {
		GL_CALL(glUniform3i(GetUniformLocation(name), vec.x, vec.y, vec.z));
	}

	void OpenGLShader::SetUniformVec4i(const std::string& name, const glm::ivec4& vec) {
		GL_CALL(glUniform4i(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w));
	}

	void OpenGLShader::SetUniform1f(const std::string& name, const float num) {
		GL_CALL(glUniform1f(GetUniformLocation(name), num));
	}

	void OpenGLShader::SetUniformVec2f(const std::string& name, const glm::vec2& vec) {
		GL_CALL(glUniform2f(GetUniformLocation(name), vec.x, vec.y));
	}

	void OpenGLShader::SetUniformVec3f(const std::string& name, const glm::vec3& vec) {
		GL_CALL(glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z));
	}

	void OpenGLShader::SetUniformVec4f(const std::string& name, const glm::vec4& vec) {
		GL_CALL(glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w));
	}

	void OpenGLShader::SetUniformMat3f(const std::string& name, const glm::mat3& mat) {
		GL_CALL(glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)));
	}

	void OpenGLShader::SetUniformMat4f(const std::string& name, const glm::mat4& mat) {
		GL_CALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)));
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
