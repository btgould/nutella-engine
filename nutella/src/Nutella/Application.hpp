#pragma once

#include "Window.hpp"

#include "Nutella/Events/ApplicationEvent.hpp"
namespace Nutella {

	class Application {
	  public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void run();

	  private:
		bool OnWindowClose(WindowClosedEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// client decides how to obtain application
	Application* CreateApplication();

} // namespace Nutella
