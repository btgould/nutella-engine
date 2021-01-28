#include "ntpch.hpp"
#include "LinuxWindow.hpp"

namespace Nutella {
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props) {
		return new LinuxWindow(props);
	}

	LinuxWindow::LinuxWindow(const WindowProps& props) {
		Init(props);
	}

	LinuxWindow::~LinuxWindow() {
		Shutdown();
	}

	void LinuxWindow::Init(const WindowProps& props) {
		// save window properties
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		NT_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width,
					 props.Height);

		// check if GLFW needs to be initialized
		if (!s_GLFWInitialized) {
			int success = glfwInit();
			NT_CORE_ASSERT(success, "GLFW failed to initialize");

			s_GLFWInitialized = true;
		}

		// create new GLFW window
		m_Window = glfwCreateWindow((int) props.Width, (int) props.Height,
									m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data); // what does this do?
		SetVSync(true);
	}

	void LinuxWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void LinuxWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void LinuxWindow::SetVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool LinuxWindow::IsVSync() const {
		return m_Data.VSync;
	}

} // namespace Nutella
