#include "ntpch.hpp"

#include "Platform/Linux/LinuxInput.hpp"

#include "Nutella/Core/Application.hpp"
#include "Nutella/Input/KeyCodes.hpp"

#include <GLFW/glfw3.h>

namespace Nutella {
	// NOTE: platform dependent, should add ifdef?
	ScopedRef<Input> Input::s_instance = CreateScopedRef<LinuxInput>();

	bool LinuxInput::isKeyPressedImpl(int keycode) {
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		return glfwGetKey(window, NTKeyToGLFWKey(keycode)) == GLFW_PRESS;
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
