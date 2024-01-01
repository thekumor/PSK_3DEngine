#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 vertexColor;
uniform vec4 uCameraPos;
uniform vec4 uCameraRotation;

void main()
{
	vertexColor = color;
	gl_Position = position + uCameraPos + uCameraRotation;
}