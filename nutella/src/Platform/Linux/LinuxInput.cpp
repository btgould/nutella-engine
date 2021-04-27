#include "ntpch.hpp"

#include "Platform/Linux/LinuxInput.hpp"

#include "Nutella/Application.hpp"

#include <GLFW/glfw3.h>

namespace Nutella {
	Input* Input::s_instance = new LinuxInput();

	bool LinuxInput::isKeyPressedImpl(int keycode) {
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		return glfwGetKey(window, keycode) == GLFW_PRESS;
	}

	bool LinuxInput::isMouseButtonPressedImpl(int button) {
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		return glfwGetMouseButton(window, button) == GLFW_PRESS;
	}

	std::pair<float, float> LinuxInput::getMousePosImpl() {
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return {(float) xpos, (float) ypos};
	}

	float LinuxInput::getMouseXImpl() {
		auto [x, y] = getMousePosImpl();
		return x;
	}

	float LinuxInput::getMouseYImpl() {
		auto [x, y] = getMousePosImpl();
		return y;
	}
} // namespace Nutella
