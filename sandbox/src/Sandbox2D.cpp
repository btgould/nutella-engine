#include "Sandbox2D.hpp"

#include <Nutella/Renderer/Renderer2D.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

Sandbox2D::Sandbox2D()
	: Layer("2D Rendering Test"),
	  m_CameraController((float) Nutella::Application::get().getWindow().GetWidth() /
							 (float) Nutella::Application::get().getWindow().GetHeight(),
						 true),
	  m_Color(1.0f, 0.0f, 0.0f, 1.0f) {}

void Sandbox2D::OnAttach() {}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(Nutella::Timestep ts) {
	m_CameraController.OnUpdate(ts);

	Nutella::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Nutella::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, m_Color);
	Nutella::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Nutella::Event& event) {
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("2D Rendering Test");
	ImGui::ColorPicker4("Square Color", glm::value_ptr(m_Color));
	ImGui::End();
}
