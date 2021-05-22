#pragma once

#include "RendererAPI.hpp"
#include "OrthographicCamera.hpp"

#include "VertexArray.hpp"

namespace Nutella {
	class Renderer {
	  public:
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Submit(std::shared_ptr<VertexArray>& vao, std::shared_ptr<Shader>& shader);

		inline static RendererAPI::API getAPI() { return RendererAPI::GetAPI(); }

	  private:
		struct SceneData {
			glm::mat4 ViewProjMat;
		};

		static SceneData* m_SceneData;
	};
} // namespace Nutella
