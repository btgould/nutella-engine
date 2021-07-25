#include "Nutella/Renderer/Renderer.hpp"

#include "RendererCommand.hpp"
#include "Renderer2D.hpp"

namespace Nutella {
	ScopedRef<Renderer::SceneData> Renderer::m_SceneData = CreateScopedRef<Renderer::SceneData>();

	void Renderer::Init() {
		NT_PROFILE_FUNC();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::BeginScene(const OrthographicCamera& camera) {
		NT_PROFILE_FUNC();

		m_SceneData->ViewProjMat = camera.GetVPMat();
	}
	void Renderer::EndScene() {}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		NT_PROFILE_FUNC();

		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::Submit(Ref<VertexArray>& vao, Ref<Shader>& shader,
						  const glm::mat4& modelTRS /*= glm::mat4(1)*/) {
		NT_PROFILE_FUNC();

		shader->Bind();
		shader->SetUniformMat4f("u_VP", m_SceneData->ViewProjMat);
		shader->SetUniformMat4f("u_ModelTRS", modelTRS);

		vao->Bind();
		RenderCommand::DrawIndexed(vao);
	}

} // namespace Nutella
