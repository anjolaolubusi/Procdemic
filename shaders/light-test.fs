#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 NewPos;

uniform vec3 viewPos;
uniform vec3 obj_Color;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	//vec3 specular;
	float shininess;
};


struct DirLight{
    vec3 direction;
	vec3 color;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	bool isOn;
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
	bool isOn;
};

struct SpotLight{
	vec3 position;
	vec3 direction;
	float cutOff;

	vec3 color;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
	bool isOn;
};

#define NR_POINT_LIGHTS 1

uniform PointLight pointLight[1];
uniform SpotLight spotLight[1];
uniform DirLight dirlight;

uniform Material material;

vec3 getDirLights(DirLight light, vec3 normal, vec3 viewDir);
vec3 getPointLights(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 getSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

uniform bool hasDirLight;
uniform bool hasPointLight;
uniform bool hasSpotLight;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	
	//vec3 result = getDirLights(dirlight, norm, viewDir);
	vec3 result = vec3(0.0);
	if(hasDirLight){
		result += getDirLights(dirlight, norm, viewDir);
	}	

	if(hasPointLight){
		for(int i=0; i < NR_POINT_LIGHTS; i++){
			result += getPointLights(pointLight[i], norm, FragPos, viewDir);
		}
	}

	if(hasSpotLight){
		for(int i=0; i < NR_POINT_LIGHTS; i++){
			result += getSpotLight(spotLight[i], norm, FragPos, viewDir);
		}
	}

	FragColor = vec4(result, 1.0);
}

vec3 getDirLights(DirLight light, vec3 Normal, vec3 viewDir){
	if(light.isOn == true){
		vec3 ambient = light.color * light.ambient * texture(material.diffuse, texCoord).rgb;

		vec3 lightDir = normalize(-light.direction);
		float diff = max(dot(Normal, lightDir), 0.0);
		vec3 diffuse = dirlight.color * diff * texture(material.diffuse, texCoord).rgb;

		vec3 reflectDir = reflect(-lightDir, Normal);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = spec * light.color * light.specular * texture(material.specular, texCoord).rgb;

		return (ambient + diffuse + specular);
	}else{
		return vec3(0.0);
	}
}

vec3 getPointLights(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	if(light.isOn == true){
	    vec3 lightDir = normalize(light.position - fragPos);
	    // diffuse shading
	    float diff = max(dot(normal, lightDir), 0.0);
	    // specular shading
	    vec3 reflectDir = reflect(-lightDir, normal);
	    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	    // attenuation
	    float distance = length(light.position - fragPos);
	    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
	    // combine results
	    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord)); 
	    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
	    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));
	    ambient *= attenuation;
	    diffuse *= attenuation;
	    specular *= attenuation;
	    return (ambient + diffuse + specular);
	}else{
		return vec3(0.0);
	}
}

vec3 getSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	if(light.isOn == true){
		vec3 lightDir = normalize(light.position - fragPos);
		float theta = dot(lightDir, normalize(-light.direction));
		if(theta > light.cutOff){	
		    // diffuse shading
		    float diff = max(dot(normal, lightDir), 0.0);
		    // specular shading
		    vec3 reflectDir = reflect(-lightDir, normal);
		    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		    // attenuation
		    float distance = length(light.position - fragPos);
		    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
		    // combine results
		    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord)); 
		    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
		    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));
		    ambient *= attenuation;
		    diffuse *= attenuation;
		    specular *= attenuation;
		    return (ambient + diffuse + specular);
		}else{
			return vec3(0.0);
		}
	}else{
		return vec3(0.0);
	}
}
