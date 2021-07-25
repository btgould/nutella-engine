#pragma once

#include <Nutella.hpp>

using namespace Nutella;
class Sandbox2D : public Layer {
  public:
	Sandbox2D();
	virtual ~Sandbox2D() {};

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Timestep ts) override;
	virtual void OnEvent(Event& event) override;
	virtual void OnImGuiRender() override;

  private:
	Ref<VertexArray> m_VAO;
	ShaderLibrary m_ShaderLibrary;
	OrthoCamController m_CameraController;

	Sprite2D m_Sprite1;
	Sprite2D m_Sprite2;
};
