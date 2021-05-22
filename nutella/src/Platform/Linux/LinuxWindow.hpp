#pragma once

#include "Nutella/Window.hpp"

#include "Nutella/Renderer/GraphicsContext.hpp"
#include "GLFW/glfw3.h"

namespace Nutella {
	// class representing a platform specific window for linux systems
	class LinuxWindow : public Window {
	  public:
		LinuxWindow(const WindowProps& props);
		~LinuxWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline virtual void* getNativeWindow() const override { return m_Window; }

		// window attributes
		// ----------------------------------------------------------------------------------

		inline void SetEventCallback(const EventCallbackFn& callback) override {
			m_Data.EventCallback = callback;
		}

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	  private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

} // namespace Nutella
