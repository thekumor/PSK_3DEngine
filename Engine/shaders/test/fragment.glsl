#version 410 core

out vec4 outputColor;
in vec4 vertexColor;
uniform float uBrightness;

void main()
{
	outputColor = vec4(vertexColor.x * uBrightness, vertexColor.g * uBrightness, vertexColor.b * uBrightness, 1.0);
}