#include "Shader.h"

Shader::Shader(const char* shaderName, Logger* logger) {
	this->logger = logger;
	for (int i = 0; i < NUM_OF_SHADERS; i++) {
		switch (i)
		{
		case VERTSHADER:
			char fileDir[100];
			sprintf(fileDir, "shaders/%s.vs", shaderName);
			this->fp_shaders = fopen(fileDir, "r");
			if (this->fp_shaders == NULL) {
				throw "Vertex Shader not found";
			}
			fclose(this->fp_shaders);
		default:
			break;
		}
	}
}

Shader::~Shader() {
	fclose(fp_shaders);
}