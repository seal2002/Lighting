#version 330 core
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 FragPos;
in vec3 Normal;

out vec4 color;

uniform Material material;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	// Ambient
	vec3 ambient = lightColor * material.ambient;
	
	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = lightColor * (diff * material.diffuse);

	// Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflecDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflecDir), 0.0f), material.shininess);
	vec3 specular = lightColor * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0f);
}