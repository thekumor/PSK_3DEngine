#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;

out vec4 vertexColor;
out vec2 vertexTexCoord;

uniform vec4 uCameraPos;
uniform vec4 uCameraRotation;
uniform float uCameraRotRadians;

vec4 RotatePoint(vec4 point, float radians)
{
	float deg = degrees(radians);

	float sinus = sin(deg);
	float cosinus = cos(deg);

	float x = point.x;
	float y = point.y;
	float z = point.z;
	float w = point.w;

	float xp = x * cosinus - y * sinus;
	float yp = x * sinus + y * cosinus;

	vec4 newPoint = vec4(xp, yp, z, w);

	return newPoint;
}

void main()
{
	vertexColor = color;
	vertexTexCoord = texCoord;

	gl_Position = position + uCameraPos;
	gl_Position = RotatePoint(gl_Position, uCameraRotRadians);
}