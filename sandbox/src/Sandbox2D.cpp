#include "Sandbox2D.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

Sandbox2D::Sandbox2D()
	: Layer("2D Rendering Test"),
	  m_CameraController((float) Nutella::Application::get().getWindow().GetWidth() /
							 (float) Nutella::Application::get().getWindow().GetHeight(),
						 true),
	  m_Pos(-0.0f, 0.0f), m_Size(1.0f, 1.0f), m_Color(1.0f, 0.0f, 0.0f, 1.0f) {}

void Sandbox2D::OnAttach() {
	m_Texture = Nutella::Texture2D::Create("nutella/res/textures/dog.png");
	m_Texture->CreateMipmaps();
}

void Sandbox2D::OnDetach() {
	m_Texture->~Texture();
}

void Sandbox2D::OnUpdate(Nutella::Timestep ts) {
	m_CameraController.OnUpdate(ts);

	float moveSpeed = 0.05;
	if (Nutella::Input::isKeyPressed(NT_KEY_RIGHT)) {
		m_Pos.x += moveSpeed;
	} else if (Nutella::Input::isKeyPressed(NT_KEY_LEFT)) {
		m_Pos.x -= moveSpeed;
	}
	if (Nutella::Input::isKeyPressed(NT_KEY_UP)) {
		m_Pos.y += moveSpeed;
	} else if (Nutella::Input::isKeyPressed(NT_KEY_DOWN)) {
		m_Pos.y -= moveSpeed;
	}

	Nutella::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Nutella::Renderer2D::DrawQuad(m_Pos, m_Size, m_Color);
	Nutella::Renderer2D::DrawQuad({0.5f, 0.5f, -0.1}, 30.0f, {1.0f, 1.0f}, m_Texture,
								  {0.5f, 0.5f, 1.0f, 1.0f});
	Nutella::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Nutella::Event& event) {
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("2D Rendering Test");
	ImGui::ColorPicker4("Quad Color", glm::value_ptr(m_Color));

	ImGui::SliderFloat2("Quad Position", glm::value_ptr(m_Pos), -3, 3);
	ImGui::SliderFloat2("Quad Size", glm::value_ptr(m_Size), 0, 5);
	ImGui::End();
}
