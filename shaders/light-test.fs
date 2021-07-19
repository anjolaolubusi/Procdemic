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


struct DirLight{
    vec3 direction;
	vec3 color;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight{
	vec3 position;
	vec3 color;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform PointLight light[1];
uniform DirLight dirlight;

uniform Material material;

vec3 getDirLights(DirLight light, vec3 normal, vec3 viewDir);
vec3 getPointLights(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result = getDirLights(dirlight, norm, viewDir);

	for(int i=0; i < 1; i++)
		result += getPointLights(light[i], norm, FragPos, viewDir);

	FragColor = vec4(result, 1.0);
}

vec3 getDirLights(DirLight light, vec3 Normal, vec3 viewDir){
	vec3 ambient = light.color * light.ambient * texture(material.diffuse, texCoord).rgb;

	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(Normal, lightDir), 0.0);
	vec3 diffuse = dirlight.color * diff * texture(material.diffuse, texCoord).rgb;

	vec3 reflectDir = reflect(-lightDir, Normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * light.color * light.specular * texture(material.specular, texCoord).rgb;

	return (ambient + diffuse + specular);
}

vec3 getPointLights(PointLight light, vec3 norm,vec3 fragPos, vec3 viewDir){

    vec3 ambient = light.ambient * texture(material.diffuse, texCoord).rgb;

    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoord).rgb;

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, texCoord).rgb;

    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient  *= attenuation;
    diffuse   *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}
