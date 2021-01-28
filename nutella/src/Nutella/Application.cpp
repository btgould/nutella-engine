#include "ntpch.hpp"

#include "Nutella/Application.hpp"

#include "Nutella/Events/ApplicationEvent.hpp"
#include "Nutella/Events/Event.hpp"
#include "Log.hpp"

#include "GLFW/glfw3.h"

namespace Nutella {
	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {}

	void Application::run() {
		while (m_Running) {
			glClearColor(0, 0.2, 0.8, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
} // namespace Nutella
