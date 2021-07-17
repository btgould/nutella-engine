#pragma once

#include <Nutella.hpp>

class Sandbox2D : public Nutella::Layer {
  public:
	Sandbox2D();
	virtual ~Sandbox2D() {};

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Nutella::Timestep ts) override;
	virtual void OnEvent(Nutella::Event& event) override;
	virtual void OnImGuiRender() override;

  private:
	Nutella::Ref<Nutella::VertexArray> m_VAO;
	Nutella::ShaderLibrary m_ShaderLibrary;
	Nutella::OrthoCamController m_CameraController;

	Nutella::Ref<Nutella::Texture> m_Texture;

	glm::vec2 m_Pos;
	glm::vec2 m_Size;
	glm::vec4 m_Color;
};
