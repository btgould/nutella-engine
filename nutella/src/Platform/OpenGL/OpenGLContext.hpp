#pragma once

#include "Nutella/Renderer/GraphicsContext.hpp"
#include "GLFW/glfw3.h"

namespace Nutella {
	class OpenGLContext : public GraphicsContext {
	  public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	  private:
		GLFWwindow* m_Window;
	};
} // namespace Nutella
