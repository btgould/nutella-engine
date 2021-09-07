#include "Sandbox2D.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

Sandbox2D::Sandbox2D()
	: Layer("2D Rendering Test"),
	  m_CameraController((float) Application::get().getWindow().GetWidth() /
							 (float) Application::get().getWindow().GetHeight(),
						 true) {}

void Sandbox2D::OnAttach() {
	m_Sprite1.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	m_Sprite2.position = glm::vec3(0.5f, 0.5f, 0.0f);
	m_Sprite2.rotation = glm::radians(30.0f);
	m_Sprite2.texture = Texture2D::Create("nutella/res/textures/dog_transparent.png");
	m_Sprite2.texRepeatFactor = 2;
	m_Sprite2.color = glm::vec4(0.6f, 0.6f, 1.0f, 1.0f);
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(Timestep ts) {
	NT_PROFILE_FUNC();

	m_CameraController.OnUpdate(ts);

	float moveSpeed = 0.05;
	if (Input::isKeyPressed(NT_KEY_RIGHT)) {
		m_Sprite1.position.x += moveSpeed;
	} else if (Input::isKeyPressed(NT_KEY_LEFT)) {
		m_Sprite1.position.x -= moveSpeed;
	}
	if (Input::isKeyPressed(NT_KEY_UP)) {
		m_Sprite1.position.y += moveSpeed;
	} else if (Input::isKeyPressed(NT_KEY_DOWN)) {
		m_Sprite1.position.y -= moveSpeed;
	}

	Renderer2D::BeginScene(m_CameraController.GetCamera());
	Renderer2D::DrawSprite(m_Sprite1);
	Renderer2D::DrawRotatedSprite(m_Sprite2);
	Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Event& event) {
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender() {
	NT_PROFILE_FUNC();

	ImGui::Begin("2D Rendering Test");
	ImGui::ColorPicker4("Quad Color", glm::value_ptr(m_Sprite1.color));

	ImGui::SliderFloat3("Quad Position", glm::value_ptr(m_Sprite1.position), -3, 3);
	ImGui::SliderFloat2("Quad Size", glm::value_ptr(m_Sprite1.size), 0, 5);
	ImGui::End();
}
