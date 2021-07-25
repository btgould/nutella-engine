#include "OrthoCamController.hpp"

#include "Nutella/Core/Core.hpp"

#include "Nutella/Input/Input.hpp"
#include "Nutella/Input/KeyCodes.hpp"

namespace Nutella {
	OrthoCamController::OrthoCamController(float aspectRatio, bool rotationEnabled)
		: m_AspectRatio(aspectRatio), m_RotationEnabled(rotationEnabled), m_ZoomLevel(1.0f),
		  m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel,
				   m_ZoomLevel) {}

	void OrthoCamController::OnUpdate(Timestep ts) {
		NT_PROFILE_FUNC();

		float mvStep = m_CamMoveSpeed * ts * m_ZoomLevel;
		float rotStep = m_CamRotationSpeed * ts;

		if (Input::isKeyPressed(NT_KEY_D)) {
			m_Camera.Move({mvStep, 0, 0});
		} else if (Input::isKeyPressed(NT_KEY_A)) {
			m_Camera.Move({-mvStep, 0, 0});
		}

		if (Input::isKeyPressed(NT_KEY_W)) {
			m_Camera.Move({0, mvStep, 0});
		} else if (Input::isKeyPressed(NT_KEY_S)) {
			m_Camera.Move({0, -mvStep, 0});
		}

		if (m_RotationEnabled) {
			if (Input::isKeyPressed(NT_KEY_Q)) {
				m_Camera.Rotate(rotStep);
			} else if (Input::isKeyPressed(NT_KEY_E)) {
				m_Camera.Rotate(-rotStep);
			}
		}
	}

	void OrthoCamController::OnEvent(Event& event) {
		NT_PROFILE_FUNC();

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(
			BIND_EVENT_FN(OrthoCamController::OnMouseScrolledEvent));
		dispatcher.Dispatch<WindowResizedEvent>(
			BIND_EVENT_FN(OrthoCamController::OnWindowResizeEvent));
	}

	bool OrthoCamController::OnMouseScrolledEvent(MouseScrolledEvent& event) {
		NT_PROFILE_FUNC();

		m_ZoomLevel -= event.GetYOffset() * m_CamZoomSpeed;
		m_ZoomLevel = std::clamp(m_ZoomLevel, 0.25f, 10.0f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
							   -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthoCamController::OnWindowResizeEvent(WindowResizedEvent& event) {
		NT_PROFILE_FUNC();

		m_AspectRatio = (float) event.GetWidth() / (float) event.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
							   -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
} // namespace Nutella
