#pragma once

#include "Event.hpp"

#include <sstream>

namespace Nutella {
	class WindowResizedEvent : public Event {
	  public:
		WindowResizedEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {};

		inline unsigned int GetWidth() {
			return m_Width;
		}

		inline unsigned int GetHeight() {
			return m_Height;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizedEvent: [" << m_Width << ", " << m_Height << "]";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResized)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	  private:
		unsigned int m_Width, m_Height;
	};

	class WindowClosedEvent : public Event {
	  public:
		WindowClosedEvent() {};

		EVENT_CLASS_TYPE(WindowClosed)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppTickEvent : public Event {
	  public:
		AppTickEvent() {};

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppUpdateEvent : public Event {
	  public:
		AppUpdateEvent() {};

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppRenderEvent : public Event {
	  public:
		AppRenderEvent() {};

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

} // namespace Nutella
