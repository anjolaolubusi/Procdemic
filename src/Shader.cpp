#include "Shader.h"

//Constructor
Shader::Shader(std::string shaderName, Logger* logger) {
	this->logger = logger;
	this->ShaderName = shaderName;
#ifdef _WIN32
    this->fileDir = "shaders\\" + shaderName;
#else
    this->fileDir = "shaders/" + shaderName;
#endif
	this->shaderProgram = glCreateProgram();
	for (int i = 0; i < NUM_OF_SHADERS; i++) {
		LoadShaderFile(i);
		glAttachShader(this->shaderProgram, this->Shaders[i]);
	}
	glLinkProgram(this->shaderProgram);
	int success;
	char infoLog[512];
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
        int tt;
		glGetProgramInfoLog(this->shaderProgram, sizeof(infoLog), &tt, infoLog);
		error_string = infoLog;
		this->logger->Log("Shader Program Linking Failed", true);
		this->logger->Log(error_string.c_str(), true);
		throw error_string.c_str();
	}
	this->logger->Log("Shader Program has been compiled");


	this->Uniforms[TRANS_UNIFROM] = glGetUniformLocation(this->shaderProgram, "transform");
	this->Uniforms[CAMERA_UNIFORM] = glGetUniformLocation(this->shaderProgram, "camera");
}

Shader::Shader(std::string vertexShader, std::string fragShader, Logger* logger) {
	this->logger = logger;
	this->shaderProgram = glCreateProgram();
	for (int i = 0; i < NUM_OF_SHADERS; i++) {
		if (i == 0) {
			this->ShaderName = vertexShader;
#ifdef _WIN32
			this->fileDir = "shaders\\" + vertexShader;
#else
			this->fileDir = "shaders/" + vertexShader;
#endif
			LoadShaderFile(i);
			glAttachShader(this->shaderProgram, this->Shaders[i]);
		}
		else {
			this->ShaderName = vertexShader;
#ifdef _WIN32
			this->fileDir = "shaders\\" + fragShader;
#else
			this->fileDir = "shaders/" + fragShader;
#endif
			LoadShaderFile(i);
			glAttachShader(this->shaderProgram, this->Shaders[i]);
		}
	}
	glLinkProgram(this->shaderProgram);
	int success;
	char infoLog[512];
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		int tt;
		glGetProgramInfoLog(this->shaderProgram, sizeof(infoLog), &tt, infoLog);
		error_string = infoLog;
		this->logger->Log("Shader Program Linking Failed", true);
		this->logger->Log(error_string.c_str(), true);
		throw error_string.c_str();
	}
	this->logger->Log("Shader Program has been compiled");

	this->Uniforms[TRANS_UNIFROM] = glGetUniformLocation(this->shaderProgram, "transform");
	this->Uniforms[CAMERA_UNIFORM] = glGetUniformLocation(this->shaderProgram, "camera");
}

//Activates Shader
void Shader::Use(){
	glUseProgram(this->shaderProgram);
}


//Loads the Shader files (Vertex and Fragment)
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
	std::string UpdateString = "Opening Shader File: " + temp_fileDir;
	this->logger->Log(UpdateString.c_str());
	if (shaderFile.is_open()){
		while (shaderFile.good()){
			getline(shaderFile, currLine);
			ShaderFiles[ShaderType].append(currLine + "\n");
		}
	} else {
		this->error_string = "Unable to load " + this->ShaderName + " Shader file. DIR: " + temp_fileDir;
		this->logger->Log(error_string.c_str(), true);
		throw this->error_string.c_str();
	}
	shaderFile.close();
	this->logger->Log("Shader File has been opened");
	const GLchar* temp = this->ShaderFiles[ShaderType].c_str();
	glShaderSource(this->Shaders[ShaderType], 1, &temp, NULL);
	this->logger->Log("Copying Shader File to OpenGL Shader Object");
	glCompileShader(this->Shaders[ShaderType]);
	int success;
	char infoLog[512];
	glGetShaderiv(this->Shaders[ShaderType], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(this->Shaders[ShaderType], 512, NULL, infoLog);
		this->error_string = "Shader Vertex Compilation Failed \n" + std::string(infoLog);
		this->logger->Log(this->error_string.c_str(), true);
		throw this->error_string.c_str();
	}
	logger->Log("OpenGL Shader has been compiled");
}

//Updates varibles in the Vertex shader
void Shader::Update(Transform& transform, Camera& camera){
	glUniformMatrix4fv(this->Uniforms[TRANS_UNIFROM], 1, false, &transform.GetModel()[0][0]);
	glUniformMatrix4fv(this->Uniforms[CAMERA_UNIFORM], 1, false, &camera.cameraMatrix()[0][0]);
}

//Clears out Shader
Shader::~Shader() {
	for (int i = 0; i < NUM_OF_SHADERS; i++) {
        glDetachShader(this->shaderProgram, this->Shaders[i]);
		glDeleteShader(this->Shaders[i]);
	}
	glDeleteProgram(this->shaderProgram);
    this->logger->Log("Shader is deleted from memory");
}
