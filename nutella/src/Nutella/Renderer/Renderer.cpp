#include "Nutella/Renderer/Renderer.hpp"

#include "RendererCommand.hpp"

namespace Nutella {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(const OrthographicCamera& camera) {
		m_SceneData->ViewProjMat = camera.GetVPMat();
	}

	void Renderer::EndScene() {}

	void Renderer::Submit(Ref<VertexArray>& vao, Ref<Shader>& shader,
						  const glm::mat4& modelTRS /*= glm::mat4(1)*/) {
		shader->Bind();
		shader->SetUniformMat4f("u_VP", m_SceneData->ViewProjMat);
		shader->SetUniformMat4f("u_ModelTRS", modelTRS);

		vao->Bind();
		RenderCommand::DrawIndexed(vao);
	}

} // namespace Nutella
