#pragma once

#include "RendererAPI.hpp"
#include "OrthographicCamera.hpp"

#include "VertexArray.hpp"

namespace Nutella {
	class Renderer {
	  public:
		static void Init();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Submit(Ref<VertexArray>& vao, Ref<Shader>& shader,
						   const glm::mat4& modelTRS = glm::mat4(1));

		inline static RendererAPI::API getAPI() { return RendererAPI::GetAPI(); }

	  private:
		struct SceneData {
			glm::mat4 ViewProjMat;
		};

		static SceneData* m_SceneData;
	};
} // namespace Nutella
