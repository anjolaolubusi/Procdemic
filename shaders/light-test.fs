#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform vec3 lightPos;
uniform vec3 lightColour;
uniform vec3 viewPos;
uniform vec3 obj_Color;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
 
struct Light {
	vec3 position;
	vec3 color;  
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;  

 
uniform Material material;

void main()
{
	vec3 ambient = material.ambient * light.color * light.ambient;

	vec3 lightDir = normalize(light.position - FragPos);  	
	float diff = max(dot(Normal, lightDir), 0.0);
	vec3 diffuse = material.diffuse * light.color * light.diffuse * diff;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, Normal); 	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (material.specular * spec) * light.color * light.specular;  

	vec3 result = (ambient + diffuse + specular) * obj_Color;

	FragColor = texture(ourTexture, texCoord) * vec4(result, 1.0);
} 
