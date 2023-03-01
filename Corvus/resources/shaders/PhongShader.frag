#version 330 core

out vec4 outColor ;

in vec2 uv;
in vec3 normal ;
in vec3 localPos ;

struct Light
{
	//0 = sun light
	//1 = point light
	int type ;
	vec3 position ;
	vec3 direction ;
	vec3 color;
	//constant, linear, quadratic
	vec3 attenuation ;
};
uniform Light lights[2] ;

struct Material 
{
	float ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};  

uniform Material material;
uniform vec3 cameraPos ;

float CalculateAttenuation(vec3 lightPosition, vec3 lightAttenuation)
{
	float dist = length(lightPosition - localPos);
	float attenuation = 1.0f / (lightAttenuation.x + lightAttenuation.y * dist + lightAttenuation.z * (dist * dist));
	return attenuation ;
}
vec3 CalculateAmbient(vec3 lightColor)
{
	return lightColor * material.ambient ;
}
vec3 CalculateDiffuse(vec3 lightDir, vec3 norNormal, vec3 lightColor)
{
	float diff = max(dot(norNormal, lightDir), 0.0) ;
	vec3 diffuse = diff * material.diffuse * lightColor ;
	return diffuse ;
}
vec3 CalculateSpecular(vec3 lightDir, vec3 norNormal, vec3 lightColor)
{
	vec3 reflectDir = reflect(-lightDir, norNormal);
	vec3 viewDir = normalize(cameraPos - localPos);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * material.specular * lightColor ;
	return specular ;
}
vec3 CalculateSunLight(in Light light, in vec3 norNormal)
{
	vec3 lightDir = normalize(-light.direction);
	vec3 ambient = CalculateAmbient(light.color);
	vec3 diffuse = CalculateDiffuse(lightDir, norNormal, light.color);
	vec3 specular = CalculateSpecular(lightDir, norNormal, light.color);
	return (ambient + diffuse + specular);
}
vec3 CalculatePointLight(in Light light, vec3 norNormal)
{
	vec3 lightDir = normalize(light.position - localPos);
	vec3 ambient = CalculateAmbient(light.color);
	vec3 diffuse = CalculateDiffuse(lightDir, norNormal, light.color);
	vec3 specular = CalculateSpecular(lightDir, norNormal, light.color);
	float atte = CalculateAttenuation(light.position, light.attenuation);
	return (ambient + diffuse + specular) * atte;
}
void main()
{		
	vec3 norNormal = normalize(normal);
	vec3 result = vec3(0.0, 0.0, 0.0);
	for(int i = 0 ; i < 2; i++)
	{
		if(lights[i].type == 0)
			result += CalculateSunLight(lights[i], norNormal);
		else if(lights[i].type == 1)
			result += CalculatePointLight(lights[i], norNormal);
	}
	outColor = vec4(result, 1.0);
}