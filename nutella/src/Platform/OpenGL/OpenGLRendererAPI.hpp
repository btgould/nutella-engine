#include "Nutella/Renderer/RendererAPI.hpp"

namespace Nutella {
	class OpenGLRendererAPI : public RendererAPI {
		virtual void SetClearColor(glm::vec4 color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(std::shared_ptr<VertexArray>& vao) override;
	};
} // namespace Nutella
