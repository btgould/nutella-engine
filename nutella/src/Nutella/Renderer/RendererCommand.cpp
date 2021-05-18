#include "RendererCommand.hpp"

#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Nutella
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();   
} // namespace Nutella
