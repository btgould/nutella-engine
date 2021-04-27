#pragma once

#include "Nutella/Input.hpp"

namespace Nutella {
	class LinuxInput : public Input {
	  protected:
		virtual bool isKeyPressedImpl(int keycode) override;

		virtual bool isMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> getMousePosImpl() override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;
	};
} // namespace Nutella
