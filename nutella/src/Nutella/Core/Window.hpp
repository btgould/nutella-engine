#pragma once

#include "ntpch.hpp"

#include "Nutella/Events/Event.hpp"

namespace Nutella {
	// struct storing simple information about a window
	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Nutella Engine", unsigned int width = 940,
					unsigned int height = 600)
			: Title(title), Width(width), Height(height) {}
	};

	// platform independent interface representing a graphical window
	class Window {
	  public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};

		// function to be called each frame to update the window
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* getNativeWindow() const = 0;

		// creates a new window with the given window properties
		static Window* Create(const WindowProps& props = WindowProps());
	};

} // namespace Nutella
