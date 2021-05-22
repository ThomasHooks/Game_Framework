#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_texPos;

uniform mat4 u_camera;

out vec2 v_texPos;

void main() {
	v_texPos = a_texPos;
	gl_Position = u_camera * vec4(a_pos, 1.0);
}