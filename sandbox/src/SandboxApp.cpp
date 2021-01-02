#include "Nutella.hpp"

class Sandbox : public Nutella::Application {
  public:
	Sandbox() {}

	~Sandbox() {}
};

Nutella::Application* Nutella::CreateApplication() {
	return new Sandbox();
}