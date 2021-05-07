#include <Nutella.hpp>

#include "imgui.h"

class ExampleLayer : public Nutella::Layer {
  public:
	ExampleLayer() : Layer("Example") {};

	void OnUpdate() override {
		if (Nutella::Input::isKeyPressed(NT_KEY_TAB)) {
			NT_TRACE("Tab is pressed");
		}
	}

	void OnEvent(Nutella::Event& event) override {
		// NT_TRACE("{0}", event);
	}

	void OnImGuiRender() override {
		ImGui::Begin("Sandbox Window");
		ImGui::Text("This is a test");
		ImGui::End();
	}
};

class Sandbox : public Nutella::Application {
  public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};

Nutella::Application* Nutella::CreateApplication() {
	return new Sandbox();
}
