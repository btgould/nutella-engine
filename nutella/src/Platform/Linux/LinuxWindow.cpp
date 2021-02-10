#include "ntpch.hpp"
#include "LinuxWindow.hpp"

#include "Nutella/Events/ApplicationEvent.hpp"
#include "Nutella/Events/KeyEvent.hpp"
#include "Nutella/Events/MouseEvent.hpp"

#include "glad/glad.h"

namespace Nutella {
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int errorCode, const char* description) {
		NT_CORE_ERROR("GLFW Error ({0}): {1}", errorCode, description);
	}

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

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		// create new GLFW window
		m_Window = glfwCreateWindow((int) props.Width, (int) props.Height,
									m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		NT_CORE_ASSERT(status, "Failed to initialize Glad");

		glfwSetWindowUserPointer(m_Window,
								 &m_Data); // associates our window data w/ GLFW
		SetVSync(true);

		// set GLFW callbacks
		// 1. Create Nutella event from GLFW data, 2. pass to m_Data's callback
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width,
											   int height) {
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			WindowResizedEvent event(width, height);

			data.Width = width;
			data.Height = height;
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			WindowClosedEvent event;

			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int keycode,
										int scancode, int action, int mods) {
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			switch (action) {
				{
				case GLFW_PRESS:
					KeyPressedEvent event(keycode, 0);
					data.EventCallback(event);
					break;
				}
				{
				case GLFW_RELEASE:
					KeyReleasedEvent event(keycode);
					data.EventCallback(event);
					break;
				}
				{
				case GLFW_REPEAT:
					KeyPressedEvent event(keycode, 1);
					data.EventCallback(event);
					break;
				}
			default:
				NT_CORE_ERROR("Key action type unrecognized");
				break;
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window,
										 unsigned int keycode) {
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button,
												int action, int mods) {
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			switch (action) {
				{
				case GLFW_PRESS:
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				{
				case GLFW_RELEASE:
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			default:
				NT_CORE_ERROR("Mouse action type unrecognized");
				break;
			}
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos,
											  double yPos) {
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float) xPos, (float) yPos);
			data.EventCallback(event);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset,
										   double yOffset) {
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float) xOffset, (float) yOffset);
			data.EventCallback(event);
		});
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
