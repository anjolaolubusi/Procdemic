#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Logger.h"
#include <string>
class Shader
{
public:
	Shader(std::string shaderName, Logger* logger);
	
	Logger* logger;
	enum ListOfShaders{VERTSHADER, FRAGSHADER, NUM_OF_SHADERS};
	int Shaders[NUM_OF_SHADERS];
};
#endif
