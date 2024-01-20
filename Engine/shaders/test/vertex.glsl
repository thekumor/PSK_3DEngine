#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;

out vec4 vertexColor;
out vec2 vertexTexCoord;

uniform vec4 uCameraPos;
uniform vec4 uCameraRotation;

void main()
{
	vertexColor = color;
	vertexTexCoord = texCoord;

	gl_Position = position + uCameraPos;
}