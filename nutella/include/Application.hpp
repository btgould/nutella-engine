#pragma once

namespace Nutella {

	class Application {
	  public:
		Application();
		virtual ~Application();

		void run();
	};

	// client decides how to obtain application
	Application* CreateApplication();

} // namespace Nutella