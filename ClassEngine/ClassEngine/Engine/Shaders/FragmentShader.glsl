#version 450 core

struct Material
{
	sampler2D diffuseMap;
	float shininess;
	float transparency;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Light
{
	vec3 lightPos;
	float ambient;
	float diffuse;
	float specular;
	vec3 lightColor;
};

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

uniform Material material;
uniform Light light;
uniform vec3 viewPosition;

out vec4 fColour;

void main()
{
	vec3 ambient = light.ambient * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.lightColor;
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPosition); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.lightColor;

	
	vec3 viewDir = normalize(viewPosition - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * material.specular) * light.lightColor;

	vec3 result = ambient + diffuse + specular;
	fColour = vec4(result, material.transparency);
}