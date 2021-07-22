#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 texCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 transform;
uniform mat4 camera;
uniform mat4 inv_model;

void main()
{
    gl_Position = camera * transform * vec4(aPos, 1.0);
    texCoord = aTexCoord;
	Normal = normalize(mat3(inv_model) * aNormal);
	FragPos = vec3(transform * vec4(aPos, 1.0));
}
