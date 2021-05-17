#include "Nutella/Renderer/Renderer.hpp"

#include "glad/glad.h"

namespace Nutella {
	RenderAPI Renderer::renderAPI = RenderAPI::OPEN_GL;

	/*void Renderer::setClearColor(float red, float green, float blue, float alpha) {
		glClearColor(red, green, blue, alpha);
	}

	void Renderer::clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::render(const VertexArray& VAO, const Shader& shader) {
		VAO.Bind();
		shader.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}*/

} // namespace Nutella
