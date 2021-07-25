#pragma once

#include "OrthographicCamera.hpp"

#include "glm/glm.hpp"

#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace Nutella {
	struct Sprite2D {
		// position of sprite (z-coord used for depth sorting)
		glm::vec3 position = glm::vec3(0.0f);
		// factor to scale sprite by in x/y directions
		glm::vec2 size = glm::vec2(1.0f);
		// rotation of the sprite counterclockwise, in radians
		float rotation = 0.0f;

		// if no texture is used, this is the flat color to render the sprite in. Otherwise, it
		// represents a "tint" to be applied to the texture by scaling each color channel by some
		// amount (e.g. {1.0, 0.5, 0.5, 1.0} tints red)
		glm::vec4 color = glm::vec4(1.0f);
		// texture to render on the sprite
		Ref<Texture> texture;
		// factor to scale all tex coords by, effectively repeating the given texture
		float texRepeatFactor = 1.0f;
	};

	class Renderer2D {
	  public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawSprite(Sprite2D& sprite);
		static void DrawRotatedSprite(Sprite2D& sprite);

	  private:
		static Ref<VertexArray> m_VertexArray;
		static Ref<Shader> m_Shader;
		static Ref<Texture> m_WhiteTex;
	};
} // namespace Nutella
