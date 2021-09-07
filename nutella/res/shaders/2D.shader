#shader vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_texCoord;

uniform mat4 u_VP;
uniform mat4 u_ModelTRS;

uniform float u_RepeatFactor;

out vec2 v_TexCoord;

void main() {
	v_TexCoord = a_texCoord * u_RepeatFactor;
	gl_Position = u_VP * u_ModelTRS * a_position;
};

#shader fragment
#version 330 core

in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

layout(location = 0) out vec4 color;

void main() {
	color = texture(u_Texture, v_TexCoord) * u_Color;

	if (color.w == 0)
		discard;
};
