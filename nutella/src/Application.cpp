#include "Application.hpp"

#include "Events/Event.hpp"
#include "Events/KeyEvent.hpp"
#include "Log.hpp"

namespace Nutella {
	Application::Application() {}

	Application::~Application() {}

	void Application::run() {
		KeyReleasedEvent e(5);

		if (e.isInCategory(EventCategoryApplication)) {
			NT_CORE_TRACE(e);
		} else {
			NT_CORE_WARN(e);
		}

		while (true)
			;
	}
} // namespace Nutella