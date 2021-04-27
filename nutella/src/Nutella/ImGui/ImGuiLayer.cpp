#include "ntpch.hpp"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include "Nutella/Core.hpp"
#include "Nutella/Application.hpp"
#include "Nutella/KeyCodes.hpp"

#include "ImGuiLayer.hpp"

// TEMP: needed for delta t + viewport
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Nutella {
	ImGuiLayer::ImGuiLayer() : Layer("ImGui Layer"), app(Application::get()) {}

	ImGuiLayer::~ImGuiLayer() {}

	void ImGuiLayer::OnAttach() {
		// initialize ImGui
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// set ImGui keybindings
		io.KeyMap[ImGuiKey_Tab] = NT_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = NT_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = NT_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = NT_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = NT_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = NT_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = NT_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = NT_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = NT_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = NT_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = NT_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = NT_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = NT_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = NT_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = NT_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = NT_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = NT_KEY_A; // for text edit CTRL+A: select all
		io.KeyMap[ImGuiKey_C] = NT_KEY_C; // for text edit CTRL+C: copy
		io.KeyMap[ImGuiKey_V] = NT_KEY_V; // for text edit CTRL+V: paste
		io.KeyMap[ImGuiKey_X] = NT_KEY_X; // for text edit CTRL+X: cut
		io.KeyMap[ImGuiKey_Y] = NT_KEY_Y; // for text edit CTRL+Y: redo
		io.KeyMap[ImGuiKey_Z] = NT_KEY_Z; // for text edit CTRL+Z: undo

		// HACK: this assumes we are using OpenGL
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach() {}

	void ImGuiLayer::OnUpdate() {
		// update window size
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(app.getWindow().GetWidth(), app.getWindow().GetHeight());

		// update delta T
		float time = (float) glfwGetTime();
		io.DeltaTime = (m_Time > 0.0f) ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event) {
		EventDistpatcher dispatcher(event);

		// bind dispatch functions for mouse button events
		dispatcher.Dispatch<MouseButtonPressedEvent>(
			BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(
			BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));

		// bind dispatch functions for key events
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));

		// bind dispatch functions for window events
		dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.GetYOffset();
		io.MouseWheelH += e.GetXOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		// set any needed modifiers
		io.KeyCtrl = io.KeysDown[NT_KEY_LEFT_CONTROL] || io.KeysDown[NT_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[NT_KEY_LEFT_SHIFT] || io.KeysDown[NT_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[NT_KEY_LEFT_ALT] || io.KeysDown[NT_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[NT_KEY_LEFT_SUPER] || io.KeysDown[NT_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();

		int keycode = e.GetKeyCode();

		if (keycode > 0 && keycode < 0x10000) {
			io.AddInputCharacter((unsigned short) keycode);
		}

		return false;
	}

	bool ImGuiLayer::OnWindowResizedEvent(WindowResizedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

		// FIXME: THIS SHOULD BE TEMPORARY
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

} // namespace Nutella
