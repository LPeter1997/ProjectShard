#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in vec4 pos;

void main()
{
	float intensity = 1.0 / length(pos.xy - light_pos);
	color = vec4(0.2, 0.3, 1.0, 1.0) * intensity;
}