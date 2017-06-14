#version 330 core
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	//vec3 position; No longer necessery when using directional lights
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

out vec4 color;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
	// Ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	// Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflecDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflecDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0f);
}