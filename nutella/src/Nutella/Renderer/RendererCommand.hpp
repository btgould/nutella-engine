#pragma once

#include "RendererAPI.hpp"

namespace Nutella {
	class RenderCommand {
	  public:
		inline static void Init() { s_RendererAPI->Init(); }

		inline static void SetClearColor(glm::vec4 color) { s_RendererAPI->SetClearColor(color); }
		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void DrawIndexed(Ref<VertexArray>& vao) { s_RendererAPI->DrawIndexed(vao); }

	  private:
		static RendererAPI* s_RendererAPI;
	};
} // namespace Nutella
