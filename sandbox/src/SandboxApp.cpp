#include <Nutella.hpp>

#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"

class ExampleLayer : public Nutella::Layer {
  public:
	ExampleLayer() : Layer("Example") {};

	void OnUpdate(Nutella::Timestep ts) override {
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
	RenderingLayer()
		: Layer("Rendering Test"),
		  m_Camera(0, Nutella::Application::get().getWindow().GetWidth(), 0,
				   Nutella::Application::get().getWindow().GetHeight()) {

		// -------------------------------------------------------------------------
		// ----------------------- Fragment Rendering ------------------------------
		// -------------------------------------------------------------------------

		// Vertex buffer (stores data about vertices)
		float fragVertices[] = {
			-50.0f, -50.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Vertex 1
			50.0f,	-50.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Vertex 2
			50.0f,	50.0f,	0.0f, 0.0f, 1.0f, 0.0f, // Vertex 3
			-50.0f, 50.0f,	0.0f, 0.0f, 0.0f, 1.0f	// Vertex 4
		};

		std::shared_ptr<Nutella::VertexBuffer> fragVertexBuffer;
		fragVertexBuffer.reset(Nutella::VertexBuffer::Create(fragVertices, sizeof(fragVertices)));

		// Index Buffer (list of order to render vertices)
		unsigned int fragIndices[] = {0, 1, 2, 2, 3, 0};

		std::shared_ptr<Nutella::IndexBuffer> fragIndexBuffer;
		fragIndexBuffer.reset(Nutella::IndexBuffer::Create(fragIndices, sizeof(fragIndices)));

		// Vertex array (combines vertex buffer + index buffer)
		Nutella::VertexBufferLayout fragLayout;
		fragLayout.push(Nutella::VertexAttribType::FLOAT, 3, false); // position
		fragLayout.push(Nutella::VertexAttribType::FLOAT, 3, false); // color

		m_FragVertexArray.reset(
			Nutella::VertexArray::Create(fragLayout, fragVertexBuffer, fragIndexBuffer));

		// Shader (colors geometry)
		m_FragShader.reset(Nutella::Shader::Create("nutella/res/shaders/MVP.shader"));

		// -------------------------------------------------------------------------
		// ------------------------ Texture Rendering ------------------------------
		// -------------------------------------------------------------------------

		float texVertices[] = {
			-50.0f, -50.0f, 0.0f, 0.0f, 0.0f, // Vertex 1
			50.0f,	-50.0f, 0.0f, 2.0f, 0.0f, // Vertex 2
			50.0f,	50.0f,	0.0f, 2.0f, 2.0f, // Vertex 3
			-50.0f, 50.0f,	0.0f, 0.0f, 2.0f  // Vertex 4
		};

		std::shared_ptr<Nutella::VertexBuffer> texVertexBuffer;
		texVertexBuffer.reset(Nutella::VertexBuffer::Create(texVertices, sizeof(texVertices)));

		unsigned int texIndices[] = {0, 1, 2, 2, 3, 0};

		std::shared_ptr<Nutella::IndexBuffer> texIndexBuffer;
		texIndexBuffer.reset(Nutella::IndexBuffer::Create(texIndices, sizeof(texIndices)));

		Nutella::VertexBufferLayout texLayout;
		texLayout.push(Nutella::VertexAttribType::FLOAT, 3, false); // position
		texLayout.push(Nutella::VertexAttribType::FLOAT, 2, false); // tex coord

		m_TexVertexArray.reset(
			Nutella::VertexArray::Create(texLayout, texVertexBuffer, texIndexBuffer));

		m_TexShader.reset(Nutella::Shader::Create("nutella/res/shaders/Tex.shader"));

		// Texture (wraps around geometry)
		m_Texture.reset(Nutella::Texture::Create("nutella/res/textures/dog.png"));
		m_Texture->CreateMipmaps();
	};

	void OnUpdate(Nutella::Timestep ts) override {
		// TEMP: this should be set by the model itself
		m_FragShader->Bind();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(400.0, 400.0, 0.0));
		m_FragShader->SetUniformMat4f("u_Model", model);

		m_TexShader->Bind();
		model = glm::translate(glm::mat4(1.0f), glm::vec3(600.0, 400.0, 0.0));
		m_TexShader->SetUniformMat4f("u_Model", model);
		m_TexShader->SetUniform1i("u_Texture", 0);

		if (Nutella::Input::isKeyPressed(NT_KEY_RIGHT)) {
			m_Camera.Move({m_CamMoveSpeed * ts, 0, 0});
		} else if (Nutella::Input::isKeyPressed(NT_KEY_LEFT)) {
			m_Camera.Move({-m_CamMoveSpeed * ts, 0, 0});
		}

		if (Nutella::Input::isKeyPressed(NT_KEY_UP)) {
			m_Camera.Move({0, m_CamMoveSpeed * ts, 0});
		} else if (Nutella::Input::isKeyPressed(NT_KEY_DOWN)) {
			m_Camera.Move({0, -m_CamMoveSpeed * ts, 0});
		}

		if (Nutella::Input::isKeyPressed(NT_KEY_Q)) {
			m_Camera.Rotate(m_CamRotSpeed * ts);
		} else if (Nutella::Input::isKeyPressed(NT_KEY_E)) {
			m_Camera.Rotate(-m_CamRotSpeed * ts);
		}

		Nutella::Renderer::BeginScene(m_Camera);
		Nutella::Renderer::Submit(m_FragVertexArray, m_FragShader);
		Nutella::Renderer::Submit(m_TexVertexArray, m_TexShader);
		Nutella::Renderer::EndScene();
	}

	void OnImGuiRender() override {
		glm::vec3 localCameraPos = m_Camera.GetPosition();
		float localCameraRot = m_Camera.GetRotation();

		ImGui::Begin("Renderer Test");
		if (ImGui::CollapsingHeader("Camera Controls")) {
			ImGui::SliderFloat2("Camera Pos", &localCameraPos.x, 0, 500);
			ImGui::SliderFloat("Camera Rotation", &localCameraRot, 0, 360);

			ImGui::SliderFloat("Camera Move Speed", &m_CamMoveSpeed, 200, 800);
			ImGui::SliderFloat("Camera Rotation Speed", &m_CamRotSpeed, 30, 360);
		}
		ImGui::End();

		m_Camera.SetPosition(localCameraPos);
		m_Camera.SetRotation(localCameraRot);
	}

  private:
	std::shared_ptr<Nutella::VertexArray> m_FragVertexArray, m_TexVertexArray;
	std::shared_ptr<Nutella::Shader> m_FragShader, m_TexShader;
	std::shared_ptr<Nutella::Texture> m_Texture;
	Nutella::OrthographicCamera m_Camera;

	float m_CamMoveSpeed = 500.0f;
	float m_CamRotSpeed = 90.0f;
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
