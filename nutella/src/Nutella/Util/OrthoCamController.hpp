#pragma once

#include "Nutella/Renderer/OrthographicCamera.hpp"

#include "Nutella/Events/Event.hpp"
#include "Nutella/Events/MouseEvent.hpp"
#include "Nutella/Events/ApplicationEvent.hpp"

#include "Nutella/Core/Timestep.hpp"

namespace Nutella {
	class OrthoCamController {
	  public:
		OrthoCamController(float aspectRatio, bool rotationEnabled = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& event);

		inline const OrthographicCamera& GetCamera() const { return m_Camera; }

	  private:
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnWindowResizeEvent(WindowResizedEvent& event);

	  private:
		float m_AspectRatio;
		float m_ZoomLevel;
		OrthographicCamera m_Camera;

		float m_CamMoveSpeed = 3.0f;
		float m_CamRotationSpeed = 180.0f;
		float m_CamZoomSpeed = 0.25f;

		bool m_RotationEnabled;
	};
} // namespace Nutella
