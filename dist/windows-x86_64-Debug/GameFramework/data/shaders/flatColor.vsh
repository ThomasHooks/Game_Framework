#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_texCord;

uniform mat4 u_camera;

out vec2 v_texCord;

void main() {
	v_texCord = a_texCord;
	gl_Position = u_camera * vec4(a_pos, 1.0);
}