#include "Nutella/Renderer/Renderer.hpp"

#include "RendererCommand.hpp"

namespace Nutella {
	void Renderer::BeginScene() {}

	void Renderer::EndScene() {}

	void Renderer::DrawIndexed(std::shared_ptr<VertexArray>& vao) {
		vao->Bind();
		RenderCommand::DrawIndexed(vao);
	}

} // namespace Nutella
