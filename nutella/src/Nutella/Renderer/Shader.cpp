#include "ntpch.hpp"
#include "Shader.hpp"

namespace Nutella {
	void ShaderLibrary::Add(const Ref<Shader>& shader) {
		std::string name = shader->GetName();
		Add(name, shader);
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
		NT_CORE_ASSERT(!Exists(name), "Shader already in library!");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath) {
		Ref<Shader> shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
		Ref<Shader> shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name) {
		NT_CORE_ASSERT(Exists(name), "Shader does not exist!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) {
		return m_Shaders.find(name) != m_Shaders.end();
	}
} // namespace Nutella
