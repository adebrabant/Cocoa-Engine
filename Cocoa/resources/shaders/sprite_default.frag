#version 330 core
			
out vec4 FragColor;

in vec2 v_TexCoord;
in vec4 v_Color;

uniform sampler2D u_Texture;
uniform vec4 u_Tint;
			
void main()
{
	FragColor = texture(u_Texture, v_TexCoord) * v_Color * u_Tint;
}