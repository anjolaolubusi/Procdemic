#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform vec3 lightPos;
uniform vec3 lightColour;
uniform vec3 viewPos;

void main()
{
	float ambientStrength = 0.3;
	vec3 ambient = ambientStrength * lightColour;
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(Normal, lightDir), 0.0);
	vec3 diffuse = diff * lightColour;
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, Normal); 	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColour;  
	vec3 result = (ambient + diffuse + specular) * vec3(1, 1, 0);
	FragColor = vec4(result, 1.0);
} 
