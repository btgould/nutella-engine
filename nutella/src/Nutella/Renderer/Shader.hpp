#pragma once

#include <string>

namespace Nutella {
	class Shader {
	  public:
		Shader(std::string& vertexSrc, std::string& fragmentSrc);
		~Shader();

		void Bind();
		void Unbind();

	  private:
		uint32_t m_RendererID;
	};
} // namespace Nutella
