#include "OrthographicCamera.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace Nutella {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_Position({0.0f, 0.0f, 0.0f}), m_Rotation(0), m_View(glm::mat4(1.0f)),
		  m_Proj(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)) {
		m_VP = m_Proj * m_View;
	}

	OrthographicCamera::~OrthographicCamera() {}

	void OrthographicCamera::UpdateView() {
		glm::mat4 pos = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), {0.0f, 0.0f, 1.0f});
		m_View = glm::inverse(pos * rot);

		m_VP = m_Proj * m_View;
	}
} // namespace Nutella
