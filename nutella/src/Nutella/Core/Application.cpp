#include "ntpch.hpp"
#include "Nutella/Core/Application.hpp"
#include "Log.hpp"

#include "Nutella/Core/Core.hpp"
#include "Nutella/Events/Event.hpp"

#include "Nutella/Renderer/Renderer.hpp"
#include "Nutella/Renderer/RendererCommand.hpp"

// TEMP: needed to get application time
#include "GLFW/glfw3.h"

namespace Nutella {

	// Singleton instance of Application
	Application* Application::s_Instance = nullptr;

	Application::Application() : m_Time(0) {
		NT_PROFILE_FUNC();

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
		NT_PROFILE_FUNC();
		// m_ImGuiLayer deleted by layer stack
	}

	void Application::OnEvent(Event& e) {
		NT_PROFILE_FUNC();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::run() {
		NT_PROFILE_FUNC();

		while (m_Running) {
			NT_PROFILE_SCOPE("Run Loop");

			RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
			RenderCommand::Clear();

			Timestep frameTime = 0;
			{
				NT_PROFILE_SCOPE("Frame Prep");

				// calculate delta time of previous frame
				float prevTime = m_Time;
				m_Time = glfwGetTime();
				frameTime = m_Time - prevTime;
			}

			{
				NT_PROFILE_SCOPE("Update Layer Stack");
				if (!m_Minimized) {
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(frameTime);
				}
			}

			{
				NT_PROFILE_SCOPE("Update ImGui Layer Stack");
				m_ImGuiLayer->begin();
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
				m_ImGuiLayer->end();
			}

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer) {
		NT_PROFILE_FUNC();
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(Layer* layer) {
		NT_PROFILE_FUNC();
		m_LayerStack.PopLayer(layer);
		layer->OnDetach();
	}

	void Application::PushOverlay(Layer* overlay) {
		NT_PROFILE_FUNC();
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::PopOverlay(Layer* overlay) {
		NT_PROFILE_FUNC();
		m_LayerStack.PopOverlay(overlay);
		overlay->OnDetach();
	}

	bool Application::OnWindowClose(WindowClosedEvent& e) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizedEvent& e) {
		NT_PROFILE_FUNC();
		uint32_t width = e.GetWidth();
		uint32_t height = e.GetHeight();

		if (width == 0 || height == 0) {
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		Renderer::OnWindowResize(width, height);
		return false;
	}

} // namespace Nutella
