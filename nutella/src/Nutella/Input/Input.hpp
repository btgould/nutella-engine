#pragma once

namespace Nutella {
	class Input {
	  public:
		inline static bool isKeyPressed(int keycode) {
			return s_instance->isKeyPressedImpl(keycode);
		}

		inline static bool isMouseButtonPressed(int button) {
			return s_instance->isMouseButtonPressedImpl(button);
		}

		inline static std::pair<float, float> getMousePos() {
			return s_instance->getMousePosImpl();
		}

		inline static float getMouseX() { return s_instance->getMouseXImpl(); }

		inline static float getMouseY() { return s_instance->getMouseYImpl(); }

	  protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;

		virtual bool isMouseButtonPressedImpl(int keycode) = 0;
		virtual std::pair<float, float> getMousePosImpl() = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;

	  private:
		static Input* s_instance;
	};
} // namespace Nutella
