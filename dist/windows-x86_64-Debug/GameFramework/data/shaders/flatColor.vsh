#version 330 core

layout(location = 0) in vec3 a_pos;

uniform mat4 u_camera;
uniform vec4 u_color;

out vec4 v_color;

void main() {
	v_color = u_color;
	gl_Position = u_camera * vec4(a_pos, 1.0);
}