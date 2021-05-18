#pragma once

#include "RendererAPI.hpp"

#include "VertexArray.hpp"

namespace Nutella {
	class Renderer {
	  public:
		static void BeginScene();
		static void EndScene();

		static void DrawIndexed(std::shared_ptr<VertexArray>& vao);

		inline static RendererAPI::API getAPI() {
			return RendererAPI::GetAPI();
		}
	};
} // namespace Nutella
