#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D current;
uniform sampler2D previos;
uniform bool blurOn = true;
uniform bool blurOnly = true;
// viewport
uniform float vx = 1;
uniform float vy = 1;
//

float weight[9] = float[](
	1,2,1,	
	2,4,2,	
	1,2,1	
);

vec4 blur(vec2 uv)
{
	vec4 result = vec4(0);
	vec2 tex_offset = 1.0 / textureSize(previos, 0);
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1, index = (i+1)*(j+1) + j + 1; j <= 1; j++)
		{
			//vec2 texel = vec2(vx,vy) * (0.5 * gl_FragCoord.xy + vec2(j, i)) / vec2(textureSize(previos, 0));
			//vec2 texel = (gl_FragCoord.xy*0.5) / vec2(textureSize(previos, 0) + vec2(j, i)*tex_offset)*vec2(vx,vy);
			//result += vec4(texture(previos, clamp((texel), vec2(0), vec2(1))).rgb * weight[index], 1);  
			//result += vec4(texture(previos, clamp((texel), vec2(0), vec2(1))).rgb * weight[index], 1);  
			result += vec4(texture(previos, uv + vec2(j, i)*tex_offset).rgb * weight[index], 1);  
		}
	}
	return result / 16.0;
}

void main()
{             
	vec2 texel = vec2(vx,vy) * gl_FragCoord.xy / vec2(textureSize(current, 0));
	if (blurOnly)
	{
		FragColor = blur(TexCoords);
	}
	else 
	{
		vec2 uv = 0.5 * vec2(vx,vy) * gl_FragCoord.xy / vec2(textureSize(previos, 0));
		FragColor = texture(current, clamp(texel, vec2(0), vec2(1))) + (blurOn ? blur(uv) : vec4(0));
	}
}