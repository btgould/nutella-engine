#include "ntpch.hpp"

#include "Nutella/Application.hpp"

#include "Nutella/Events/ApplicationEvent.hpp"
#include "Nutella/Events/Event.hpp"
#include "Log.hpp"

namespace Nutella {
	Application::Application() {}

	Application::~Application() {}

	void Application::run() {
		WindowClosedEvent e = WindowClosedEvent();

		if (e.isInCategory(EventCategoryApplication)) {
			NT_CORE_TRACE(e);
		} else {
			NT_CORE_WARN(e);
		}

		while (true)
			;
	}
} // namespace Nutella