#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexPos;

uniform mat4 mvp;

out vec2 texPos;

void main() {
	texPos = aTexPos;
	gl_Position = mvp * vec4(aPos, 1.0);
}