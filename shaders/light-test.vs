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
uniform float u_scale;
uniform bool showHeight;

uniform ivec3[12] grads;
uniform int[512] perm;


vec3 chooseGrad(int index, vec3 pos){
return (dot(pos, grads[index])/dot(grads[index], grads[index]))*pos;
}

float snoise(vec2 st){
vec2 m_st = st * 20;
float n0, n1, n2;

float F2 = 0.5*(sqrt(3.0)-1.0);
float s = (m_st.x + m_st.y)*F2;
int i = int(floor(m_st.x+s));
int j = int(floor(m_st.y+s));

float G2 = (3.0-sqrt(3.0))/6.0;
float t = (i+j)*G2;
float X0 = i-t;
float Y0 = j-t;
float x0 = m_st.x - X0;
float y0 = m_st.y - Y0;

int i1, j1;
if(x0 > y0){
i1 = 1;
j1 = 0;
}else{
i1=0;
j1=1;
}

float x1 = x0 - i1 + G2;
float y1 = y0 - j1 + G2;
float x2 = x0 - 1.0 + 2.0*G2;
float y2 = y0 - 1.0 + 2.0*G2;

int ii = i & 255;
int jj = j & 255;

int gi0 = int(mod(perm[ii + perm[jj]], 12));
int gi1 = int(mod(perm[ii + i1 + perm[jj+j1]], 12));
int gi2 = int(mod(perm[ii + 1 + perm[jj+1]], 12));

float t0 = 0.5 - x0*x0 - y0*y0;
if(t0 < 0){
n0 = 0.0;
}else{
t0 *= t0;
n0 = t0 * t0 * (grads[gi0].x * x0 + grads[gi0].y * y0);
}


float t1 = 0.5 - x1*x1 - y1*y1;
if(t1 < 0){
n1 = 0.0;
}else{
t1 *= t1;
n1 = t1 * t1 * (grads[gi1].x * x1 + grads[gi1].y * y1);
}


float t2 = 0.5 - x2*x2 - y2*y2;
if(t2 < 0){
n2 = 0.0;
}else{
t2 *= t2;
n2 = t2 * t2 * (grads[gi2].x * x2 + grads[gi2].y * y2);
}
float final_val = 25*(n0+n1+n2);
return final_val;
}

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

#define OCTAVES 6
float fbm (in vec2 st) {
    // Initial values
    float value = 0.0;
    float amplitude = .5;
    float frequency = 0.;
    //
    // Loop of octaves
    for (int i = 0; i < OCTAVES; i++) {
        value += amplitude * snoise(st);
        st *= 2.;
        amplitude *= .5;
    }
    return value;
}



void main()
{
	vec3 newPos = vec3(aPos.x, fbm(aPos.xz * u_scale), aPos.z);
	vec3 newNorm = cross(newPos, aNormal);
	if(showHeight){
	gl_Position = camera * transform * vec4(newPos, 1.0);
	}else{
	gl_Position = camera * transform * vec4(aPos, 1.0);
	}
	texCoord = aTexCoord;
	//Normal = normalize(mat3(inv_model) * aNormal);
	Normal = normalize(mat3(inv_model) * newNorm);
	FragPos = vec3(transform * vec4(newPos, 1.0));
	NewPos = newPos;
}
