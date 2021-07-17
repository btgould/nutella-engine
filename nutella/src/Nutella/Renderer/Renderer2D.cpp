#include "Renderer2D.hpp"
#include "RendererCommand.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace Nutella {
	Ref<VertexArray> Renderer2D::m_VertexArray;
	Ref<Shader> Renderer2D::m_Shader;

	void Renderer2D::Init() {
		float vertices[] = {
			-0.25f, -0.25f, 0.0f, // Vertex 1
			0.25f,	-0.25f, 0.0f, // Vertex 2
			0.25f,	0.25f,	0.0f, // Vertex 3
			-0.25f, 0.25f,	0.0f  // Vertex 4
		};

		Nutella::Ref<Nutella::VertexBuffer> vbo =
			Nutella::VertexBuffer::Create(vertices, sizeof(vertices));

		Nutella::VertexBufferLayout layout;
		layout.push(Nutella::VertexAttribType::FLOAT, 3, false); // Positions

		uint32_t indices[] = {0, 1, 2, 2, 3, 0};
		Nutella::Ref<Nutella::IndexBuffer> ibo =
			Nutella::IndexBuffer::Create(indices, sizeof(indices));

		m_VertexArray = Nutella::VertexArray::Create(layout, vbo, ibo);
		m_Shader = Shader::Create("nutella/res/shaders/FlatColor.shader");
	}

	void Renderer2D::Shutdown() {}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_VP", camera.GetVPMat());
	}

	void Renderer2D::EndScene() {}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({pos.x, pos.y, 0.0f}, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color) {
		m_Shader->Bind();
		m_Shader->SetUniformVec4f("u_Color", color);

		glm::mat4 modelTRS = glm::translate(glm::mat4(1.0f), pos) *
							 glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		m_Shader->SetUniformMat4f("u_ModelTRS", modelTRS);

		RenderCommand::DrawIndexed(m_VertexArray);
	}
} // namespace Nutella
