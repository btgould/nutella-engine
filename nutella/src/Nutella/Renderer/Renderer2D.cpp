#include "Renderer2D.hpp"
#include "RendererCommand.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace Nutella {
	Ref<VertexArray> Renderer2D::m_VertexArray;
	Ref<Shader> Renderer2D::m_Shader;
	Ref<Texture> Renderer2D::m_WhiteTex;

	void Renderer2D::Init() {
		NT_PROFILE_FUNC();

		float vertices[] = {
			-0.25f, -0.25f, 0.0f, 0.0f, 0.0f, // Vertex 1
			0.25f,	-0.25f, 0.0f, 1.0f, 0.0f, // Vertex 2
			0.25f,	0.25f,	0.0f, 1.0f, 1.0f, // Vertex 3
			-0.25f, 0.25f,	0.0f, 0.0f, 1.0f  // Vertex 4
		};

		Nutella::Ref<Nutella::VertexBuffer> vbo =
			Nutella::VertexBuffer::Create(vertices, sizeof(vertices));

		Nutella::VertexBufferLayout layout;
		layout.push(Nutella::VertexAttribType::FLOAT, 3, false); // Positions
		layout.push(Nutella::VertexAttribType::FLOAT, 2, false); // Texture Coords

		uint32_t indices[] = {0, 1, 2, 2, 3, 0};
		Nutella::Ref<Nutella::IndexBuffer> ibo =
			Nutella::IndexBuffer::Create(indices, sizeof(indices));

		m_VertexArray = Nutella::VertexArray::Create(layout, vbo, ibo);
		// TODO: find a way of specifying relative resource paths for client applications
		m_Shader = Shader::Create("nutella/res/shaders/2D.shader");
		m_WhiteTex = Texture2D::Create(1, 1);
	}

	void Renderer2D::Shutdown() {
		NT_PROFILE_FUNC();

		m_VertexArray->~VertexArray();
		m_Shader->~Shader();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		NT_PROFILE_FUNC();

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_VP", camera.GetVPMat());
	}

	void Renderer2D::EndScene() { NT_PROFILE_FUNC(); }

	void Renderer2D::DrawSprite(Sprite2D& sprite) {
		NT_PROFILE_FUNC();

		if (sprite.texture) {
			sprite.texture->Bind();
		} else {
			m_WhiteTex->Bind();
		}
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);
		m_Shader->SetUniformVec4f("u_Color", sprite.color);
		m_Shader->SetUniform1f("u_RepeatFactor", sprite.texRepeatFactor);

		glm::mat4 modelTRS = glm::translate(glm::mat4(1.0f), sprite.position) *
							 glm::scale(glm::mat4(1.0f), {sprite.size.x, sprite.size.y, 1.0f});
		m_Shader->SetUniformMat4f("u_ModelTRS", modelTRS);

		RenderCommand::DrawIndexed(m_VertexArray);
	}

	void Renderer2D::DrawRotatedSprite(Sprite2D& sprite) {
		NT_PROFILE_FUNC();

		if (sprite.texture) {
			sprite.texture->Bind();
		} else {
			m_WhiteTex->Bind();
		}
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);
		m_Shader->SetUniformVec4f("u_Color", sprite.color);
		m_Shader->SetUniform1f("u_RepeatFactor", sprite.texRepeatFactor);

		glm::mat4 modelTRS = glm::translate(glm::mat4(1.0f), sprite.position) *
							 glm::rotate(glm::mat4(1.0f), sprite.rotation, {0.0f, 0.0f, 1.0f}) *
							 glm::scale(glm::mat4(1.0f), {sprite.size.x, sprite.size.y, 1.0f});
		m_Shader->SetUniformMat4f("u_ModelTRS", modelTRS);

		RenderCommand::DrawIndexed(m_VertexArray);
	}
} // namespace Nutella
