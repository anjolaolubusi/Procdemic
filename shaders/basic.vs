#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 transform;
uniform mat4 camera;

void main()
{
    gl_Position = camera * transform * vec4(aPos, 1.0);
    texCoord = aTexCoord;
}

