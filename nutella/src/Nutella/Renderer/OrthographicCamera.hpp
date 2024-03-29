#pragma once

#include "Shader.hpp"

#include "glm/glm.hpp"

namespace Nutella {
	class OrthographicCamera {
	  public:
		OrthographicCamera(float left, float right, float bottom, float top);
		~OrthographicCamera();

		inline glm::mat4 GetViewMat() const { return m_View; }
		inline glm::mat4 GetProjMat() const { return m_Proj; }
		inline glm::mat4 GetVPMat() const { return m_VP; }

		inline glm::vec3 GetPosition() const { return m_Position; }
		inline float GetRotation() const { return m_Rotation; }

		void Move(const glm::vec3& mv);
		void SetPosition(const glm::vec3& pos);

		void Rotate(float rot);
		void SetRotation(const float& rot);

		void SetProjection(float left, float right, float bottom, float top);

	  private:
		void UpdateView();

		glm::mat4 m_View;
		glm::mat4 m_Proj;
		glm::mat4 m_VP;

		glm::vec3 m_Position;
		float m_Rotation;
	};
} // namespace Nutella
