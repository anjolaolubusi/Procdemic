#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Logger.h"
#include <stdio.h>

class Shader
{
public: 
	Shader(const char* shaderName, Logger* logger);
	
	Logger* logger;
	enum ListOfShaders{VERTSHADER, FRAGSHADER, NUM_OF_SHADERS};
	int Shaders[NUM_OF_SHADERS];
	FILE* fp_shaders;
	char* str_shaders[NUM_OF_SHADERS];

	~Shader();
};
#endif
