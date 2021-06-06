#include "ntpch.hpp"
#include "Nutella/Application.hpp"
#include "Log.hpp"

#include "Nutella/Core.hpp"
#include "Nutella/Events/Event.hpp"

#include "Renderer/Renderer.hpp"
#include "Renderer/RendererCommand.hpp"

// TEMP: needed to get application time
#include "GLFW/glfw3.h"

namespace Nutella {

	// Singleton instance of Application
	Application* Application::s_Instance = nullptr;

	Application::Application() : m_Time(0) {
		// ensure only one instance exists
		NT_CORE_ASSERT(!s_Instance, "Cannot create multiple instances of Application class");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {
		// m_ImGuiLayer deleted by layer stack
	}

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
			RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
			RenderCommand::Clear();

			// calculate delta time of previous frame
			float prevTime = m_Time;
			m_Time = glfwGetTime();
			Timestep frameTime = m_Time - prevTime;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(frameTime);

			m_ImGuiLayer->begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->end();

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
