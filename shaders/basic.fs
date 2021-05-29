#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D ourTexture;
uniform vec3 obj_Color;
void main()
{
    FragColor = texture(ourTexture, texCoord) * vec4(obj_Color, 1);
} 
