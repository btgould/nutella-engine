#include "Nutella/Renderer/RendererAPI.hpp"

namespace Nutella {
	class OpenGLRendererAPI : public RendererAPI {
		virtual void Init() override;

		virtual void SetClearColor(glm::vec4 color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(Ref<VertexArray>& vao) override;
	};
} // namespace Nutella
