#pragma once

#include "VertexArray.hpp"
#include "Shader.hpp"

namespace Nutella {
	enum class RenderAPI { NONE = 0, OPEN_GL = 1 };

	class Renderer {
	  public:
		/*void setClearColor(float red, float green, float blue, float alpha);
		void clear();

		void render(const VertexArray& VAO, const Shader& shader);*/

		inline static RenderAPI getAPI() {
			return renderAPI;
		}

	  private:
		static RenderAPI renderAPI;
	};
} // namespace Nutella
