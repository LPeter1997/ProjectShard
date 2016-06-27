#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform sampler2D textures[32];

in DATA
{
	vec4 position;
	vec4 color;
	vec2 uv;
	float tid;
} fs_in;

void main()
{
	vec4 texColor = fs_in.color;
	// TODO: textures
	color = fs_in.color.wzyx; // * texColor;
}