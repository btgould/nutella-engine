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

		Nutella::Ref<Nutella::VertexBuffer> fragVertexBuffer;
		fragVertexBuffer.reset(Nutella::VertexBuffer::Create(fragVertices, sizeof(fragVertices)));

		// Index Buffer (list of order to render vertices)
		unsigned int fragIndices[] = {0, 1, 2, 2, 3, 0};

		Nutella::Ref<Nutella::IndexBuffer> fragIndexBuffer;
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

		Nutella::Ref<Nutella::VertexBuffer> texVertexBuffer;
		texVertexBuffer.reset(Nutella::VertexBuffer::Create(texVertices, sizeof(texVertices)));

		unsigned int texIndices[] = {0, 1, 2, 2, 3, 0};

		Nutella::Ref<Nutella::IndexBuffer> texIndexBuffer;
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

		// Camera movement controls
		if (Nutella::Input::isKeyPressed(NT_KEY_D)) {
			m_Camera.Move({m_CamMoveSpeed * ts, 0, 0});
		} else if (Nutella::Input::isKeyPressed(NT_KEY_A)) {
			m_Camera.Move({-m_CamMoveSpeed * ts, 0, 0});
		}

		if (Nutella::Input::isKeyPressed(NT_KEY_W)) {
			m_Camera.Move({0, m_CamMoveSpeed * ts, 0});
		} else if (Nutella::Input::isKeyPressed(NT_KEY_S)) {
			m_Camera.Move({0, -m_CamMoveSpeed * ts, 0});
		}

		if (Nutella::Input::isKeyPressed(NT_KEY_Q)) {
			m_Camera.Rotate(m_CamRotSpeed * ts);
		} else if (Nutella::Input::isKeyPressed(NT_KEY_E)) {
			m_Camera.Rotate(-m_CamRotSpeed * ts);
		}

		// dog movement controls
		if (Nutella::Input::isKeyPressed(NT_KEY_RIGHT)) {
			m_DogPos += glm::vec3(m_DogMoveSpeed * ts, 0.0f, 0.0f);
		} else if (Nutella::Input::isKeyPressed(NT_KEY_LEFT)) {
			m_DogPos += glm::vec3(-m_DogMoveSpeed * ts, 0.0f, 0.0f);
		}

		if (Nutella::Input::isKeyPressed(NT_KEY_UP)) {
			m_DogPos += glm::vec3(0.0f, m_DogMoveSpeed * ts, 0.0f);
		} else if (Nutella::Input::isKeyPressed(NT_KEY_DOWN)) {
			m_DogPos += glm::vec3(0.0f, -m_DogMoveSpeed * ts, 0.0f);
		}

		// calculate model matrices
		glm::mat4 fragTRS = glm::translate(glm::mat4(1.0f), glm::vec3(400.0, 400.0, 0.0));
		glm::mat4 texTRS =
			glm::translate(glm::mat4(1.0f), m_DogPos) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_DogRot), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), m_DogScale);

		m_TexShader->Bind();
		m_TexShader->SetUniform1i("u_Texture", 0);

		Nutella::Renderer::BeginScene(m_Camera);
		Nutella::Renderer::Submit(m_FragVertexArray, m_FragShader, fragTRS);
		Nutella::Renderer::Submit(m_TexVertexArray, m_TexShader, texTRS);
		Nutella::Renderer::EndScene();
	}

	void OnImGuiRender() override {
		glm::vec3 localCameraPos = m_Camera.GetPosition();
		float localCameraRot = m_Camera.GetRotation();

		ImGui::Begin("Renderer Test");

		if (ImGui::CollapsingHeader("Object Controls", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::SliderFloat2("Position##dog", &m_DogPos.x, 0, 1000);
			ImGui::SliderFloat("Rotation##dog", &m_DogRot, 0, 360);
			ImGui::SliderFloat2("Scale##dog", &m_DogScale.x, 0, 5);

			ImGui::SliderFloat("Move Speed##dog", &m_DogMoveSpeed, 200, 800);
		}

		if (ImGui::CollapsingHeader("Camera Controls", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::SliderFloat2("Position##cam", &localCameraPos.x, 0, 500);
			ImGui::SliderFloat("Rotation##cam", &localCameraRot, 0, 360);

			ImGui::SliderFloat("Move Speed##cam", &m_CamMoveSpeed, 200, 800);
			ImGui::SliderFloat("Rotation Speed##cam", &m_CamRotSpeed, 30, 360);
		}

		ImGui::End();

		m_Camera.SetPosition(localCameraPos);
		m_Camera.SetRotation(localCameraRot);
	}

  private:
	Nutella::Ref<Nutella::VertexArray> m_FragVertexArray, m_TexVertexArray;
	Nutella::Ref<Nutella::Shader> m_FragShader, m_TexShader;
	Nutella::Ref<Nutella::Texture> m_Texture;
	Nutella::OrthographicCamera m_Camera;

	float m_CamMoveSpeed = 500.0f;
	float m_CamRotSpeed = 90.0f;

	glm::vec3 m_DogPos = {600.0f, 400.0f, 0.0f};
	glm::vec3 m_DogScale = {1.0f, 1.0f, 1.0f};
	float m_DogRot = 0.0f;
	float m_DogMoveSpeed = 500.0f;
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
