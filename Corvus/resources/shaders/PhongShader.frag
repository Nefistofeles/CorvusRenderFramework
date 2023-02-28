#version 330 core

out vec4 outColor ;

in vec2 uv;
in vec3 normal ;
in vec3 localPos ;

struct Light{
	vec3 position ;

	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light ;
struct Material {
	sampler2D diffuse;
	sampler2D specular;
    float shininess;
};  

uniform Material material;
uniform vec3 cameraPos ;


void main()
{
	vec3 ambient = light.ambient * texture(material.diffuse, uv).rgb ;
	
	vec3 norNormal = normalize(normal);
	vec3 lightDir = normalize(light.position - localPos);
	float diff = max(dot(norNormal, lightDir), 0.0) ;
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, uv).rgb ;
	
	vec3 reflectDir = reflect(-lightDir, norNormal);
	vec3 viewDir = normalize(cameraPos - localPos);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, uv).rgb ;
	
	outColor = vec4(ambient + specular + diffuse, 1.0);

}