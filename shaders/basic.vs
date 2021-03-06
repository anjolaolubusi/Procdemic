#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 texCoord;
out vec3 Normal;

uniform mat4 transform;
uniform mat4 camera;
uniform mat4 normalMatrix;

void main()
{
    gl_Position = camera * transform * vec4(aPos, 1.0);
    texCoord = aTexCoord;
    Normal = mat3(normalMatrix) * aNormal;
}

