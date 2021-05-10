#pragma once

// TODO: he does not need to include this... why do I?
#include "Nutella/Log.hpp"

// application creation implemented in client
extern Nutella::Application* Nutella::CreateApplication();

int main() {
	Nutella::Log::Init();

	Nutella::Application* app = Nutella::CreateApplication();
	app->run();
	delete app;
}
