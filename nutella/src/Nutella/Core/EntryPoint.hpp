#pragma once

#include "Nutella/Core/Log.hpp"

// application creation implemented in client
extern Nutella::Application* Nutella::CreateApplication();

int main() {
	Nutella::Log::Init();

	NT_PROFILE_BEGIN_SESSION("Startup", "NT_Startup_Profile.json");
	Nutella::Application* app = Nutella::CreateApplication();
	NT_PROFILE_END_SESSION();

	NT_PROFILE_BEGIN_SESSION("Runtime", "NT_Runtime_Profile.json");
	app->run();
	NT_PROFILE_END_SESSION();

	NT_PROFILE_BEGIN_SESSION("Shutdown", "NT_Shutdown_Profile.json");
	delete app;
	NT_PROFILE_END_SESSION();
}
