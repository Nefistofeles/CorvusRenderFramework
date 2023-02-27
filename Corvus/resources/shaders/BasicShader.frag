#version 330 core
in vec2 uv;
in vec3 normal ;
in vec3 localPos ;
out vec4 outColor ;

uniform sampler2D sampler ;

struct Light
{
	float ambient ;

	vec3 position ;
	vec3 color ;
};
uniform Light light ;
uniform vec3 cameraPos ;

void main()
{
	vec4 texColor = texture(sampler, uv);
	vec3 norNormal = normalize(normal);
	vec3 lightDir = normalize(light.position - localPos);
	float diff = max(dot(norNormal, lightDir), 0.0) ;
	vec3 diffuse = diff * light.color;

	vec3 reflectDir = reflect(-lightDir, norNormal);
	vec3 viewDir = normalize(cameraPos - localPos);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
	vec3 specular = 0.9 * spec * light.color; 
	
	vec3 color = (light.ambient + diffuse + specular)* texColor.rgb ;
	outColor = vec4(color, texColor.a);
}