#version 330 core

in vec2 v_LocalUV;
in vec2 v_MinUV;
in vec2 v_MaxUV;
in vec4 v_Color;
flat in uint v_TexIndex;
in float v_TilingFactor;

uniform sampler2D u_Textures[32];

out vec4 FragColor;
			
void main()
{
	vec4 texColor = v_Color;
	int textureIndex = int(v_TexIndex);
	vec2 tiledUV = v_LocalUV * v_TilingFactor;
	vec2 wrappedUV = fract(tiledUV);
	vec2 size = vec2(v_MaxUV.x - v_MinUV.x, v_MaxUV.y - v_MinUV.y);
	vec2 offset = vec2(size.x * wrappedUV.x, size.y * wrappedUV.y);
	vec2 textureCoord = vec2(v_MinUV.x + offset.x, v_MinUV.y + offset.y);
	switch (textureIndex)
	{
		case 0: texColor *= texture(u_Textures[0], textureCoord); break;
		case 1: texColor *= texture(u_Textures[1], textureCoord); break;
		case 2: texColor *= texture(u_Textures[2], textureCoord); break;
		case 3: texColor *= texture(u_Textures[3], textureCoord); break;
		case 4: texColor *= texture(u_Textures[4], textureCoord); break;
		case 5: texColor *= texture(u_Textures[5], textureCoord); break;
		case 6: texColor *= texture(u_Textures[6], textureCoord); break;
		case 7: texColor *= texture(u_Textures[7], textureCoord); break;
		case 8: texColor *= texture(u_Textures[8], textureCoord); break;
		case 9: texColor *= texture(u_Textures[9], textureCoord); break;
		case 10: texColor *= texture(u_Textures[10], textureCoord); break;
		case 11: texColor *= texture(u_Textures[11], textureCoord); break;
		case 12: texColor *= texture(u_Textures[12], textureCoord); break;
		case 13: texColor *= texture(u_Textures[13], textureCoord); break;
		case 14: texColor *= texture(u_Textures[14], textureCoord); break;
		case 15: texColor *= texture(u_Textures[15], textureCoord); break;
		case 16: texColor *= texture(u_Textures[16], textureCoord); break;
		case 17: texColor *= texture(u_Textures[17], textureCoord); break;
		case 18: texColor *= texture(u_Textures[18], textureCoord); break;
		case 19: texColor *= texture(u_Textures[19], textureCoord); break;
		case 20: texColor *= texture(u_Textures[20], textureCoord); break;
		case 21: texColor *= texture(u_Textures[21], textureCoord); break;
		case 22: texColor *= texture(u_Textures[22], textureCoord); break;
		case 23: texColor *= texture(u_Textures[23], textureCoord); break;
		case 24: texColor *= texture(u_Textures[24], textureCoord); break;
		case 25: texColor *= texture(u_Textures[25], textureCoord); break;
		case 26: texColor *= texture(u_Textures[26], textureCoord); break;
		case 27: texColor *= texture(u_Textures[27], textureCoord); break;
		case 28: texColor *= texture(u_Textures[28], textureCoord); break;
		case 29: texColor *= texture(u_Textures[29], textureCoord); break;
		case 30: texColor *= texture(u_Textures[30], textureCoord); break;
		case 31: texColor *= texture(u_Textures[31], textureCoord); break;
	}

	FragColor = texColor;
}