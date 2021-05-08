#pragma once

namespace Nutella {
	class GraphicsContext {
	  public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
} // namespace Nutella
