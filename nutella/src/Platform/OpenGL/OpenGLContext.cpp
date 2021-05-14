#include "ntpch.hpp"

#include "OpenGLContext.hpp"
#include "glad/glad.h"

namespace Nutella {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_Window(windowHandle) {
		NT_ASSERT(windowHandle, "[ERROR]: Graphics context received null window handle!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		NT_CORE_ASSERT(status, "Failed to initialize Glad!");

		NT_CORE_INFO("OpenGL Renderer Selected:");
		NT_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		NT_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
		NT_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_Window);
	}
} // namespace Nutella
