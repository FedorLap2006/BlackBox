#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 viewPos;
uniform samplerCube skybox;

void main()
{             
	float ratio = 1.00 / 1.1;
    vec3 I = normalize(Position - viewPos);
    vec3 R = refract(I, normalize(Normal), ratio);
	vec4 color = vec4(1.0, 0.6, 0.3, 0.4);
    FragColor = vec4(texture(skybox, R).rgb, 1.0) * color;
}
