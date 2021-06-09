#include "RendererCommand.hpp"

#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Nutella {
	ScopedRef<RendererAPI> RenderCommand::s_RendererAPI = CreateScopedRef<OpenGLRendererAPI>();
} // namespace Nutella
