#include "ntpch.hpp"
#include "Nutella/Application.hpp"
#include "Log.hpp"

#include "Nutella/Core.hpp"
#include "Nutella/Events/Event.hpp"

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

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Vertex buffer (stores data about vertices)
		float positions[] = {
			-0.5,  -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, // Vertex 1
			0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Vertex 2
			0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, // Vertex 3
			-0.5f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // Vertex 4
		};
		m_VertexBuffer.reset(VertexBuffer::Create(positions, sizeof(positions)));

		// Index Buffer (list of order to render vertices)
		unsigned int vertices[] = {0, 1, 2, 2, 3, 0};
		m_IndexBuffer.reset(IndexBuffer::Create(vertices, sizeof(vertices)));

		// Vertex array (combines vertex buffer + index buffer)
		VertexBufferLayout layout;
		layout.push<GL_FLOAT>(3, GL_FALSE); // position
		layout.push<GL_FLOAT>(3, GL_FALSE); // color
		m_VertexArray.reset(new VertexArray(layout, *m_VertexBuffer, *m_IndexBuffer));

		// Shader (colors geometry)
		m_Shader.reset(Shader::Create("nutella/res/shaders/Basic.shader"));
	}

	Application::~Application() {
		// m_ImGuiLayer deleted by layer stack
		// Do I need to delete shader here?
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
			glClearColor(0.2, 0.2, 0.2, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// OpenGL Draw call
			m_VertexArray->Bind();
			m_Shader->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetLength(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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
