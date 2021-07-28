#version 330 core

// Per Vertex Shader
in vec3 vPosition;
in vec3 vColor;

uniform mat4 vTransform;

out vec3 pColor;

void main() {
	// All in one transform for vertices.
	// vTransform = PerspectiveTransform*Rotation*Translate;
	gl_Position = vTransform * vec4(vPosition.x, vPosition.y, vPosition.z, 1.0f);
	pColor = vColor;
}