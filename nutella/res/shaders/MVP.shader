#shader vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec3 a_color;

uniform mat4 u_VP;
uniform mat4 u_Model;

out vec4 vertColor;

void main() {
	vertColor = vec4(a_color, 1.0f);
	gl_Position = u_VP * u_Model * a_position;
};

#shader fragment
#version 330 core

in vec4 vertColor;

layout(location = 0) out vec4 color;

void main() {
	color = vertColor;
};
