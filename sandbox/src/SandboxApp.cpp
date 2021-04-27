#include <Nutella.hpp>

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
};

class Sandbox : public Nutella::Application {
  public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Nutella::ImGuiLayer());
	}

	~Sandbox() {}
};

Nutella::Application* Nutella::CreateApplication() {
	return new Sandbox();
}
