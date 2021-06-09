#pragma once

#include "RendererAPI.hpp"

namespace Nutella {
	class RenderCommand {
	  public:
		inline static void Init() { s_RendererAPI->Init(); }

		inline static void SetClearColor(glm::vec4 color) { s_RendererAPI->SetClearColor(color); }
		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void DrawIndexed(Ref<VertexArray>& vao) { s_RendererAPI->DrawIndexed(vao); }

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height){
			s_RendererAPI->SetViewport(x, y, width, height);
		}

	  private:
		static ScopedRef<RendererAPI> s_RendererAPI;
	};
} // namespace Nutella
