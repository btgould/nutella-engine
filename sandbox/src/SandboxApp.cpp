#include <Nutella.hpp>
#include <Nutella/Core/EntryPoint.hpp>

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>

#include "Sandbox2D.hpp"

class RenderingLayer : public Nutella::Layer {
  public:
	RenderingLayer()
		: Layer("Rendering Test"),
		  m_CameraController((float) Nutella::Application::get().getWindow().GetWidth() /
								 (float) Nutella::Application::get().getWindow().GetHeight(),
							 true) {

		// -------------------------------------------------------------------------
		// ----------------------- Fragment Rendering ------------------------------
		// -------------------------------------------------------------------------

		// Vertex buffer (stores data about vertices)
		float fragVertices[] = {
			-0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 0.0f, // Vertex 1
			0.25f,	-0.25f, 0.0f, 1.0f, 0.0f, 0.0f, // Vertex 2
			0.25f,	0.25f,	0.0f, 0.0f, 1.0f, 0.0f, // Vertex 3
			-0.25f, 0.25f,	0.0f, 0.0f, 0.0f, 1.0f	// Vertex 4
		};

		Nutella::Ref<Nutella::VertexBuffer> fragVertexBuffer;
		fragVertexBuffer = Nutella::VertexBuffer::Create(fragVertices, sizeof(fragVertices));

		// Index Buffer (list of order to render vertices)
		unsigned int fragIndices[] = {0, 1, 2, 2, 3, 0};

		Nutella::Ref<Nutella::IndexBuffer> fragIndexBuffer;
		fragIndexBuffer = Nutella::IndexBuffer::Create(fragIndices, sizeof(fragIndices));

		// Vertex array (combines vertex buffer + index buffer)
		Nutella::VertexBufferLayout fragLayout;
		fragLayout.push(Nutella::VertexAttribType::FLOAT, 3, false); // position
		fragLayout.push(Nutella::VertexAttribType::FLOAT, 3, false); // color

		m_FragVertexArray =
			Nutella::VertexArray::Create(fragLayout, fragVertexBuffer, fragIndexBuffer);

		// Shader (colors geometry)
		m_ShaderLibrary.Load("VertexColor", "nutella/res/shaders/MVP.shader");

		// -------------------------------------------------------------------------
		// ------------------------ Texture Rendering ------------------------------
		// -------------------------------------------------------------------------

		float texVertices[] = {
			-0.25f, -0.25f, 0.0f, 0.0f, 0.0f, // Vertex 1
			0.25f,	-0.25f, 0.0f, 2.0f, 0.0f, // Vertex 2
			0.25f,	0.25f,	0.0f, 2.0f, 2.0f, // Vertex 3
			-0.25f, 0.25f,	0.0f, 0.0f, 2.0f  // Vertex 4
		};

		Nutella::Ref<Nutella::VertexBuffer> texVertexBuffer;
		texVertexBuffer = Nutella::VertexBuffer::Create(texVertices, sizeof(texVertices));

		unsigned int texIndices[] = {0, 1, 2, 2, 3, 0};

		Nutella::Ref<Nutella::IndexBuffer> texIndexBuffer;
		texIndexBuffer = Nutella::IndexBuffer::Create(texIndices, sizeof(texIndices));

		Nutella::VertexBufferLayout texLayout;
		texLayout.push(Nutella::VertexAttribType::FLOAT, 3, false); // position
		texLayout.push(Nutella::VertexAttribType::FLOAT, 2, false); // tex coord

		m_TexVertexArray = Nutella::VertexArray::Create(texLayout, texVertexBuffer, texIndexBuffer);

		m_ShaderLibrary.Load("nutella/res/shaders/2D.shader");

		// Texture (wraps around geometry)
		m_Texture = Nutella::Texture2D::Create("nutella/res/textures/dog_transparent.png");
		m_Texture->CreateMipmaps();
	};

	void OnUpdate(Nutella::Timestep ts) override {

		// Object updating
		m_CameraController.OnUpdate(ts);

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

		// Rendering
		glm::mat4 fragTRS = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
		glm::mat4 texTRS =
			glm::translate(glm::mat4(1.0f), m_DogPos) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_DogRot), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), m_DogScale);

		auto fragShader = m_ShaderLibrary.Get("VertexColor");
		auto texShader = m_ShaderLibrary.Get("2D");

		texShader->Bind();
		texShader->SetUniform1i("u_Texture", 0);
		texShader->SetUniformVec4f("u_Color", {1.0f, 1.0f, 1.0f, 1.0f});

		Nutella::Renderer::BeginScene(m_CameraController.GetCamera());
		Nutella::Renderer::Submit(m_FragVertexArray, fragShader, fragTRS);
		Nutella::Renderer::Submit(m_TexVertexArray, texShader, texTRS);
		Nutella::Renderer::EndScene();
	}

	void OnEvent(Nutella::Event& event) override { m_CameraController.OnEvent(event); }

	void OnImGuiRender() override {
		ImGui::Begin("Renderer Test");

		if (ImGui::CollapsingHeader("Object Controls", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::SliderFloat2("Position##dog", &m_DogPos.x, -3, 3);
			ImGui::SliderFloat("Rotation##dog", &m_DogRot, 0, 360);
			ImGui::SliderFloat2("Scale##dog", &m_DogScale.x, 0, 5);

			ImGui::SliderFloat("Move Speed##dog", &m_DogMoveSpeed, 1, 5);
		}

		ImGui::End();
	}

  private:
	Nutella::Ref<Nutella::VertexArray> m_FragVertexArray, m_TexVertexArray;
	Nutella::ShaderLibrary m_ShaderLibrary;
	Nutella::Ref<Nutella::Texture> m_Texture;
	Nutella::OrthoCamController m_CameraController;

	glm::vec3 m_DogPos = {0.5f, 0.25f, 0.0f};
	glm::vec3 m_DogScale = {1.0f, 1.0f, 1.0f};
	float m_DogRot = 0.0f;
	float m_DogMoveSpeed = 3.0f;
};

class Sandbox : public Nutella::Application {
  public:
	Sandbox() {
		// PushLayer(new RenderingLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox() {}
};

Nutella::Application* Nutella::CreateApplication() {
	return new Sandbox();
}
