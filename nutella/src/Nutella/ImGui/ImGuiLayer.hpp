#pragma once

#include "Nutella/Layer.hpp"

#include "Nutella/Events/MouseEvent.hpp"
#include "Nutella/Events/KeyEvent.hpp"
#include "Nutella/Events/ApplicationEvent.hpp"

namespace Nutella {
	class ImGuiLayer : public Layer {
	  public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate() override;
		void OnEvent(Event& event) override;

	  private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

		bool OnWindowResizedEvent(WindowResizedEvent& e);

	  private:
		float m_Time = 0.0f;
		Application& app;
	};
} // namespace Nutella
