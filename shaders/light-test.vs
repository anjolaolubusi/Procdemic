#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 texCoord;
out vec3 Normal;
out vec3 FragPos;
out vec3 NewPos;


uniform mat4 transform;
uniform mat4 camera;
uniform mat4 inv_model;



// 2D Random
float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))
                 * 43758.5453123);
}

// 2D Noise based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 coorners percentages
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}



void main()
{
	vec3 newPos = vec3(aPos.x, noise(aPos.xz * 20), aPos.z);
	vec3 newNorm = cross(vec3(12.44, 5.335, 42), aNormal);
	gl_Position = camera * transform * vec4(newPos, 1.0);
	texCoord = aTexCoord;
	//Normal = normalize(mat3(inv_model) * aNormal);
	Normal = normalize(mat3(inv_model) * newNorm);
	FragPos = vec3(transform * vec4(newPos, 1.0));
	NewPos = newPos;
}
