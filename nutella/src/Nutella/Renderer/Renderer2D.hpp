#pragma once

#include "OrthographicCamera.hpp"

#include "glm/glm.hpp"

#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace Nutella {
	class Renderer2D {
	  public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size,
							 const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size,
							 const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});
		static void DrawQuad(const glm::vec2& pos, const float rotation, const glm::vec2& size,
							 const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});
		static void DrawQuad(const glm::vec3& pos, const float rotation, const glm::vec2& size,
							 const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});

		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size,
							 const Ref<Texture>& texture,
							 const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size,
							 const Ref<Texture>& texture,
							 const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});
		static void DrawQuad(const glm::vec2& pos, const float rotation, const glm::vec2& size,
							 const Ref<Texture>& texture,
							 const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});
		static void DrawQuad(const glm::vec3& pos, const float rotation, const glm::vec2& size,
							 const Ref<Texture>& texture,
							 const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});

	  private:
		static Ref<VertexArray> m_VertexArray;
		static Ref<Shader> m_Shader;
		static Ref<Texture> m_WhiteTex;
	};
} // namespace Nutella
