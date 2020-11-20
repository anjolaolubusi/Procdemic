#include "Shader.h"

Shader::Shader(std::string shaderName, Logger* logger) {
	this->logger = logger;
	this->ShaderName = shaderName;
	this->fileDir = "shaders\\" + shaderName;
	this->shaderProgram = glCreateProgram();
	for (int i = 0; i < NUM_OF_SHADERS; i++) {
		LoadShaderFile(i);
		glAttachShader(this->shaderProgram, this->Shaders[i]);
	}
	glLinkProgram(this->shaderProgram);
	int success;
	char infoLog[512];
	glGetShaderiv(this->shaderProgram, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(this->shaderProgram, 512, NULL, infoLog);
		error_string = "Shader Program Linking Failed \n" + std::string(infoLog);
		throw error_string.c_str();
	}
}

void Shader::Use(){
	glUseProgram(this->shaderProgram);
}

void Shader::LoadShaderFile(int ShaderType){
	std::ifstream shaderFile;
	std::string temp_fileDir = this->fileDir;
	if (ShaderType == VERTSHADER) {
		temp_fileDir.append(".vs");
		shaderFile.open(temp_fileDir.c_str());
		this->Shaders[VERTSHADER] = glCreateShader(GL_VERTEX_SHADER);
	}else{		
		temp_fileDir.append(".fs");
		shaderFile.open(temp_fileDir.c_str());
		this->Shaders[FRAGSHADER] = glCreateShader(GL_FRAGMENT_SHADER);
	}
	std::string currLine;
	if (shaderFile.is_open()){
		while (shaderFile.good()){
			getline(shaderFile, currLine);
			ShaderFiles[ShaderType].append(currLine + "\n");
		}
	} else {
		error_string = "Unable to load " + this->ShaderName + " Shader";
		throw error_string.c_str();
	}
	shaderFile.close();
	const GLchar* temp = this->ShaderFiles[ShaderType].c_str();
	glShaderSource(this->Shaders[ShaderType], 1, &temp, NULL);
	glCompileShader(this->Shaders[ShaderType]);
	int success;
	char infoLog[512];
	glGetShaderiv(this->Shaders[ShaderType], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(this->Shaders[ShaderType], 512, NULL, infoLog);
		error_string = "Shader Vertex Compilation Failed \n" + std::string(infoLog);
		throw error_string.c_str();
	}
}


Shader::~Shader() {
	for (int i = 0; i < NUM_OF_SHADERS; i++) {
		glDeleteShader(this->Shaders[i]);
	}
	glDeleteProgram(this->shaderProgram);
}