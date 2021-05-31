#pragma once

#include "Window.hpp"

#include "Nutella/Events/ApplicationEvent.hpp"

#include "Nutella/LayerStack.hpp"
#include "Nutella/ImGui/ImGuiLayer.hpp"

namespace Nutella {

	class Application {
	  public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void run();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		inline static Application& get() { return *s_Instance; }
		inline Window& getWindow() { return *m_Window; }

	  private:
		bool OnWindowClose(WindowClosedEvent& e);

		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;

		float m_Time;

		static Application* s_Instance;
	};

	// client decides how to obtain application
	Application* CreateApplication();

} // namespace Nutella
