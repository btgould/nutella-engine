#include "ntpch.hpp"

#include "Application.hpp"

#include "Events/ApplicationEvent.hpp"
#include "Events/Event.hpp"
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