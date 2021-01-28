#pragma once

#include "Window.hpp"

namespace Nutella {

	class Application {
	  public:
		Application();
		virtual ~Application();

		void run();

	  private:
		std::unique_ptr<Window> m_Window;
        bool m_Running = true;
	};

	// client decides how to obtain application
	Application* CreateApplication();

} // namespace Nutella
