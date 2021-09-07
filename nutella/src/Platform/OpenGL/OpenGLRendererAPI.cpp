#include "OpenGLRendererAPI.hpp"

#include "glad/glad.h"
#include "glutil.hpp"

namespace Nutella {
	void OpenGLRendererAPI::Init() {
		NT_PROFILE_FUNC();

		GL_CALL(glEnable(GL_BLEND));
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		GL_CALL(glEnable(GL_DEPTH_TEST));
	}

	void OpenGLRendererAPI::SetClearColor(glm::vec4 color) {
		GL_CALL(glClearColor(color.r, color.g, color.b, color.a));
	}

	void OpenGLRendererAPI::Clear() { GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); }

	void OpenGLRendererAPI::DrawIndexed(Ref<VertexArray>& vao) {
		GL_CALL(glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT,
							   nullptr));
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		GL_CALL(glViewport(x, y, width, height));
	}
} // namespace Nutella
