#shader vertex
#version 330 core

layout(location = 0) in vec4 a_position;

uniform mat4 u_VP;
uniform mat4 u_ModelTRS;

void main() {
	gl_Position = u_VP * u_ModelTRS * a_position;
};

#shader fragment
#version 330 core

uniform vec4 u_Color;

layout(location = 0) out vec4 color;

void main() {
	color = u_Color;
};
