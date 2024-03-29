#pragma once

#include <memory>
#include "VertexArray.hpp"
#include "glm/glm.hpp"

namespace Nutella {

	class RendererAPI {
	  public:
		enum class API { NONE = 0, OPEN_GL = 1 };

		virtual void Init() = 0;

		virtual void SetClearColor(glm::vec4 color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(Ref<VertexArray>& vao) = 0;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		inline static API GetAPI() { return s_API; }

	  private:
		static API s_API;
	};

} // namespace Nutella
