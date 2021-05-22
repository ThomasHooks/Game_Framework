#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texCord;
layout(location = 3) in float a_texSlot;

uniform mat4 u_camera;

out vec4 v_color;
out vec2 v_texCord;
out float v_texSlot;

void main() 
{
	v_color = a_color;
	v_texCord = a_texCord;
	v_texSlot = a_texSlot;
	gl_Position = u_camera * vec4(a_pos, 1.0);
}