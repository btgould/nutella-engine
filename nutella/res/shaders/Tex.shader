#shader vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_texCoord;

uniform mat4 u_VP;
uniform mat4 u_Model;

out vec2 v_TexCoord;

void main() {
	v_TexCoord = a_texCoord;
	gl_Position = u_VP * u_Model * a_position;
};

#shader fragment
#version 330 core

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

layout(location = 0) out vec4 color;

void main() {
	color = texture(u_Texture, v_TexCoord);
};
