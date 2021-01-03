#pragma once

#include "Log.hpp"

extern Nutella::Application* Nutella::CreateApplication();

int main() {
	Nutella::Log::Init();

	NT_CORE_WARN("Core warning");
	NT_CLIENT_INFO("Client info");

	Nutella::Application* app = Nutella::CreateApplication();
	app->run();
	delete app;
}