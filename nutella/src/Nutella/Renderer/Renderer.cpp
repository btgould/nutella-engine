#include "Nutella/Renderer/Renderer.hpp"

#include "RendererCommand.hpp"

namespace Nutella {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(const OrthographicCamera& camera) {
		m_SceneData->ViewProjMat = camera.GetVPMat();
	}

	void Renderer::EndScene() {}

	void Renderer::Submit(std::shared_ptr<VertexArray>& vao, std::shared_ptr<Shader>& shader) {
		shader->Bind();
		shader->SetUniformMat4f("u_VP", m_SceneData->ViewProjMat);

		vao->Bind();
		RenderCommand::DrawIndexed(vao);
	}

} // namespace Nutella
