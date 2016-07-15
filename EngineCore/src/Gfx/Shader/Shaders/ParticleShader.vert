#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in float tid;
layout (location = 3) in vec2 uv;

uniform mat4 ml_matrix = mat4(1.0);
uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);

out DATA
{
	vec4 position;
	vec4 color;
	float tid;
	vec2 uv;
} vs_out;

void main()
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
	vs_out.position = ml_matrix * position;
	vs_out.uv = uv;
	vs_out.tid = tid;
	vs_out.color = color;
}