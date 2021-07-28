#version 330 core

in vec3 pColor;

out vec4 PixelColor;

void main() {
	PixelColor = vec4(pColor.x, pColor.y, pColor.z, 1.0f);
}