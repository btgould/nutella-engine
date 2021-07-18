#include "Sandbox2D.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

Sandbox2D::Sandbox2D()
	: Layer("2D Rendering Test"),
	  m_CameraController((float) Application::get().getWindow().GetWidth() /
							 (float) Application::get().getWindow().GetHeight(),
						 true),
	  m_Pos(-0.0f, 0.0f), m_Size(1.0f, 1.0f), m_Color(1.0f, 0.0f, 0.0f, 1.0f) {}

void Sandbox2D::OnAttach() {
	m_Texture = Texture2D::Create("nutella/res/textures/dog.png");
	m_Texture->CreateMipmaps();
}

void Sandbox2D::OnDetach() {
	m_Texture->~Texture();
}

void Sandbox2D::OnUpdate(Timestep ts) {
	m_CameraController.OnUpdate(ts);

	float moveSpeed = 0.05;
	if (Input::isKeyPressed(NT_KEY_RIGHT)) {
		m_Pos.x += moveSpeed;
	} else if (Input::isKeyPressed(NT_KEY_LEFT)) {
		m_Pos.x -= moveSpeed;
	}
	if (Input::isKeyPressed(NT_KEY_UP)) {
		m_Pos.y += moveSpeed;
	} else if (Input::isKeyPressed(NT_KEY_DOWN)) {
		m_Pos.y -= moveSpeed;
	}

	Renderer2D::BeginScene(m_CameraController.GetCamera());
	Renderer2D::DrawQuad(m_Pos, m_Size, m_Color);
	Renderer2D::DrawQuad({0.5f, 0.5f, -0.1}, 30.0f, {1.0f, 1.0f}, m_Texture,
						 {0.5f, 0.5f, 1.0f, 1.0f});
	Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Event& event) {
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("2D Rendering Test");
	ImGui::ColorPicker4("Quad Color", glm::value_ptr(m_Color));

	ImGui::SliderFloat2("Quad Position", glm::value_ptr(m_Pos), -3, 3);
	ImGui::SliderFloat2("Quad Size", glm::value_ptr(m_Size), 0, 5);
	ImGui::End();
}
