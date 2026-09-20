#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_LocalUV;
layout(location = 2) in vec2 a_MinUV;
layout(location = 3) in vec2 a_MaxUV;
layout(location = 4) in vec4 a_Color;
layout(location = 5) in uint a_TexIndex;
layout(location = 6) in float a_TilingFactor;

uniform mat4 u_ViewProjection;

out vec2 v_LocalUV;
out vec2 v_MinUV;
out vec2 v_MaxUV;
out vec4 v_Color;
flat out uint v_TexIndex;
out float v_TilingFactor;

void main()
{
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
	v_LocalUV = a_LocalUV;
	v_MinUV = a_MinUV;
	v_MaxUV = a_MaxUV;
	v_Color = a_Color;
	v_TexIndex = a_TexIndex;
	v_TilingFactor = a_TilingFactor;
}