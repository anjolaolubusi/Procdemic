#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Logger.h"
#include <stdio.h>
#include <fstream> 
#include "transform.h"
#include "Camera.h"

class Shader
{
public: 
	Shader(std::string shaderName, Logger* logger);
	void Use();
	void Update(Transform transform, Camera camera);
	~Shader();
	void LoadShaderFile(int ShaderType);

	Logger* logger;
	enum ListOfShaders{VERTSHADER, FRAGSHADER, NUM_OF_SHADERS};
	enum ListOfUnifroms{TRANS_UNIFROM, CAMERA_UNIFORM, NUM_OF_UNIFROMS};
	unsigned int Shaders[NUM_OF_SHADERS];
	unsigned int Uniforms[NUM_OF_UNIFROMS];
	std::string ShaderFiles[NUM_OF_SHADERS];
	std::string ShaderName;
	std::string fileDir;
	std::string error_string;
	unsigned int shaderProgram;
};
#endif
