#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 vertexColor;
uniform vec4 uCamera;

void main()
{
	vertexColor = color;
	gl_Position = position + uCamera;
}