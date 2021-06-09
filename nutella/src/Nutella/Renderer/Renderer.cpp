#include "Nutella/Renderer/Renderer.hpp"

#include "RendererCommand.hpp"

namespace Nutella {
	ScopedRef<Renderer::SceneData> Renderer::m_SceneData = CreateScopedRef<Renderer::SceneData>();

	void Renderer::Init() { RenderCommand::Init(); }

	void Renderer::BeginScene(const OrthographicCamera& camera) {
		m_SceneData->ViewProjMat = camera.GetVPMat();
	}
	void Renderer::EndScene() {}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::Submit(Ref<VertexArray>& vao, Ref<Shader>& shader,
						  const glm::mat4& modelTRS /*= glm::mat4(1)*/) {
		shader->Bind();
		shader->SetUniformMat4f("u_VP", m_SceneData->ViewProjMat);
		shader->SetUniformMat4f("u_ModelTRS", modelTRS);

		vao->Bind();
		RenderCommand::DrawIndexed(vao);
	}

} // namespace Nutella
