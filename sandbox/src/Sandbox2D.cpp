#include "Sandbox2D.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

Sandbox2D::Sandbox2D()
	: Layer("2D Rendering Test"),
	  m_CameraController((float) Nutella::Application::get().getWindow().GetWidth() /
							 (float) Nutella::Application::get().getWindow().GetHeight(),
						 true),
	  m_Color(1.0f, 0.0f, 0.0f, 1.0f) {}

void Sandbox2D::OnAttach() {
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
	Nutella::Ref<Nutella::IndexBuffer> ibo = Nutella::IndexBuffer::Create(indices, sizeof(indices));

	m_VAO = Nutella::VertexArray::Create(layout, vbo, ibo);

	m_ShaderLibrary.Load("nutella/res/shaders/FlatColor.shader");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(Nutella::Timestep ts) {
	m_CameraController.OnUpdate(ts);

	Nutella::Ref<Nutella::Shader> shader = m_ShaderLibrary.Get("FlatColor");
	shader->Bind();
	shader->SetUniformVec4f("u_Color", m_Color);

	Nutella::Renderer::BeginScene(m_CameraController.GetCamera());
	Nutella::Renderer::Submit(m_VAO, shader);
	Nutella::Renderer::EndScene();
}

void Sandbox2D::OnEvent(Nutella::Event& event) {
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("2D Rendering Test");
	ImGui::ColorPicker4("Square Color", glm::value_ptr(m_Color));
	ImGui::End();
}
