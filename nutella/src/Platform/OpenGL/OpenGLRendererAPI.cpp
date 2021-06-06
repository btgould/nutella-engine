#include "OpenGLRendererAPI.hpp"

#include "glad/glad.h"
#include "glutil.hpp"

namespace Nutella {
	void OpenGLRendererAPI::Init() {
		GL_CALL(glEnable(GL_BLEND));
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

	void OpenGLRendererAPI::SetClearColor(glm::vec4 color) {
		GL_CALL(glClearColor(color.r, color.g, color.b, color.a));
	}

	void OpenGLRendererAPI::Clear() { GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); }

	void OpenGLRendererAPI::DrawIndexed(Ref<VertexArray>& vao) {
		GL_CALL(glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT,
							   nullptr));
	}
} // namespace Nutella
