#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out vec4 outColor;

void main()
{
	vec4 eyePos = ml_matrix * position;
    gl_Position = pr_matrix * eyePos;

	outColor = color;
	
	float dist = length(eyePos.xyz);
	float att = inversesqrt(0.1f * dist);
	gl_PointSize = 50.0f * att;
}