#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex;

out vec3 sNormal;
out vec2 sTex;

void main() {
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
	sNormal = normal;
	sTex = tex;
}