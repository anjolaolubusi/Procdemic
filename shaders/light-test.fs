#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;
uniform vec3 obj_Color;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	vec3 specular;
	float shininess;
};

struct Light {
	//vec3 position;
	vec3 direction;
	vec3 color;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;


uniform Material material;

void main()
{

	vec3 ambient = light.color * light.ambient * texture(material.diffuse, texCoord).rgb;

	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(Normal, lightDir), 0.0);
	vec3 diffuse = light.color * diff * texture(material.diffuse, texCoord).rgb;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, Normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * light.color * light.specular * texture(material.specular, texCoord).rgb;

	vec3 result = (ambient + diffuse + specular);

	FragColor = vec4(result, 1.0);
}
