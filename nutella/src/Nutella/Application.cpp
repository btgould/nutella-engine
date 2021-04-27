#include "ntpch.hpp"

#include "Nutella/Core.hpp"

#include "Nutella/Application.hpp"

#include "Nutella/Events/Event.hpp"

#include "Log.hpp"

#include "glad/glad.h"

namespace Nutella {

	// Singleton instance of Application
	Application* Application::s_Instance = nullptr;

	Application::Application() {
		// ensure only one instance exists
		NT_CORE_ASSERT(!s_Instance, "Cannot create multiple instances of Application class");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application() {}

	void Application::OnEvent(Event& e) {
		EventDistpatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::run() {
		while (m_Running) {
			glClearColor(0, 0.2, 0.8, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(Layer* layer) {
		m_LayerStack.PopLayer(layer);
		layer->OnDetach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::PopOverlay(Layer* overlay) {
		m_LayerStack.PopOverlay(overlay);
		overlay->OnDetach();
	}

	bool Application::OnWindowClose(WindowClosedEvent& e) {
		m_Running = false;
		return true;
	}

} // namespace Nutella
