#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 viewPos;
uniform samplerCube skybox;

void main()
{             
    vec3 I = normalize(Position - viewPos);
    vec3 R = reflect(I, normalize(Normal));
	vec4 color = vec4(1.0, 0.5, 0.3, 0.5);
    FragColor = vec4(texture(skybox, R).rgb, 1.0) * color;
}
