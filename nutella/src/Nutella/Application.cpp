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

		// Vertex array (combines vertex buffer + index buffer)
		glGenVertexArrays(1, &m_VertexArrayID);
		glBindVertexArray(m_VertexArrayID);

		// Vertex buffer (stores data about vertices)
		float positions[3 * 3] = {
			-0.5, -0.5f, 0.0f, // Vertex 1
			0.5f, -0.5f, 0.0f, // Vertex 2
			0.0f, 0.5f,	 0.0f  // Vertex 3
		};

		glGenBuffers(1, &m_VertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

		// Index Buffer (list of order to render vertices)
		unsigned int vertices[3] = {0, 1, 2};

		glGenBuffers(1, &m_IndexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Shaders (color geometry)
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;

			void main() {
				gl_Position = vec4(a_position, 1.0f);
			};
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			void main() {
				color = vec4(0.2f, 0.2f, 0.8f, 1.0f);
			};
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
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
			glBindVertexArray(m_VertexArrayID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
			m_Shader->Bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
