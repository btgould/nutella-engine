#include "ntpch.hpp"

#include "Nutella/Application.hpp"

#include "Nutella/Events/Event.hpp"
#include "Log.hpp"

#include "GLFW/glfw3.h"

namespace Nutella {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application() {}

	void Application::OnEvent(Event& e) {
		EventDistpatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(
			BIND_EVENT_FN(Application::OnWindowClose));

		NT_CORE_TRACE("{0}", e);
	}

	void Application::run() {
		while (m_Running) {
			glClearColor(0, 0.2, 0.8, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowClosedEvent& e) {
		m_Running = false;
		return true;
	}

} // namespace Nutella
