#pragma once

#include "OrthographicCamera.hpp"

#include "glm/glm.hpp"

#include "VertexArray.hpp"
#include "Shader.hpp"

namespace Nutella {
	class Renderer2D {
	  public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);

	  private:
		static Ref<VertexArray> m_VertexArray;
		static Ref<Shader> m_Shader;
	};
} // namespace Nutella
