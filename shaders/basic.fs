#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;

uniform sampler2D ourTexture;
uniform vec3 lightcolor;
uniform vec3 ourColor;
uniform vec3 lightDir;
void main()
{
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * lightcolor;
    FragColor = texture(ourTexture, texCoord) * vec4(diffuse * ourColor, 1.0);
} 
