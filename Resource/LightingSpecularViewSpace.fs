#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;
// Extra in variable, since we need the light position in view space
// we calculate this in the vertex shader

out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	// Ambient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	// Specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(-FragPos); // The viewer is at (0,0,0) so viewDir is (0,0,0) - Position => -Position
	vec3 reflecDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflecDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	color = vec4(result, 1.0f);
}