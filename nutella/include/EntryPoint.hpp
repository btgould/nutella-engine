#pragma once

#include "Nutella.hpp"

extern Nutella::Application* Nutella::CreateApplication();

int main() {
	Nutella::Application* app = Nutella::CreateApplication();
	app->run();
	delete app;
}