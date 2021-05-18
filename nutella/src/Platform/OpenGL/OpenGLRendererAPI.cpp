#include "OpenGLRendererAPI.hpp"

#include "glad/glad.h"

namespace Nutella {

	void OpenGLRendererAPI::SetClearColor(glm::vec4 color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(std::shared_ptr<VertexArray>& vao) {
		glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
} // namespace Nutella
