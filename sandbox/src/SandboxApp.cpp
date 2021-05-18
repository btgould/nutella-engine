#include <Nutella.hpp>

#include "imgui.h"

#include "Nutella/Renderer/VertexArray.hpp"
#include "Nutella/Renderer/Shader.hpp"
#include "Nutella/Renderer/Renderer.hpp"

class ExampleLayer : public Nutella::Layer {
  public:
	ExampleLayer() : Layer("Example") {};

	void OnUpdate() override {
		if (Nutella::Input::isKeyPressed(NT_KEY_TAB)) {
			NT_TRACE("Tab is pressed");
		}
	}

	void OnEvent(Nutella::Event& event) override {
		// NT_TRACE("{0}", event);
	}

	void OnImGuiRender() override {
		ImGui::Begin("Sandbox Window");
		ImGui::Text("This is created from the sandbox client");
		ImGui::End();
	}
};

class RenderingLayer : public Nutella::Layer {
  public:
	RenderingLayer() : Layer("Rendering Test") {
		// Vertex buffer (stores data about vertices)
		float positions[] = {
			-0.5,  -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, // Vertex 1
			0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Vertex 2
			0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, // Vertex 3
			-0.5f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // Vertex 4
		};

		std::shared_ptr<Nutella::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Nutella::VertexBuffer::Create(positions, sizeof(positions)));

		// Index Buffer (list of order to render vertices)
		unsigned int vertices[] = {0, 1, 2, 2, 3, 0};

		std::shared_ptr<Nutella::IndexBuffer> indexBuffer;
		indexBuffer.reset(Nutella::IndexBuffer::Create(vertices, sizeof(vertices)));

		// Vertex array (combines vertex buffer + index buffer)
		Nutella::VertexBufferLayout layout;
		layout.push(Nutella::VertexAttribType::FLOAT, 3, false); // position
		layout.push(Nutella::VertexAttribType::FLOAT, 3, false); // color

		m_VertexArray.reset(Nutella::VertexArray::Create(layout, vertexBuffer, indexBuffer));

		// Shader (colors geometry)
		m_Shader.reset(Nutella::Shader::Create("nutella/res/shaders/Basic.shader"));
	};

	void OnUpdate() override {
		m_Shader->Bind();
		Nutella::Renderer::DrawIndexed(m_VertexArray);
	}

  private:
	std::shared_ptr<Nutella::VertexArray> m_VertexArray;
	std::shared_ptr<Nutella::Shader> m_Shader;
};

class Sandbox : public Nutella::Application {
  public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushLayer(new RenderingLayer());
	}

	~Sandbox() {}
};

Nutella::Application* Nutella::CreateApplication() {
	return new Sandbox();
}
