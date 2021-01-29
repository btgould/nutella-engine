#include <Nutella.hpp>

class ExampleLayer : public Nutella::Layer {
  public:
	ExampleLayer() : Layer("Example") {};

	void OnUpdate() override {
		NT_TRACE("Example Layer::Update");
	}

	void OnEvent(Nutella::Event& event) override {
		NT_TRACE("{0}", event);
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
