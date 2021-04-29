#pragma once

#include "Nutella/Layer.hpp"

#include "Nutella/Events/MouseEvent.hpp"
#include "Nutella/Events/KeyEvent.hpp"
#include "Nutella/Events/ApplicationEvent.hpp"

namespace Nutella {
	// forward declaration
	class Application;

	class ImGuiLayer : public Layer {
	  public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void begin();
		void end();

	  private:
		float m_Time = 0.0f;
		Application& app;
	};
} // namespace Nutella
