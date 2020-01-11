#version 330
out vec4 FragColor;

in vec3 sPos;
in vec3 sNormal;
in vec2 sTex;

void main() {
	FragColor = vec4(sNormal.x, sNormal.y, sNormal.z, 1.0f);
}