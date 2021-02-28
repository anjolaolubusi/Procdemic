#ifndef TEXTURE_H
#define TEXTURE_H
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Logger.h"
#include <stb_image/stb_image.h>

struct Texture {
	Texture(const Texture& texture) {
		this->logger = texture.logger;
		this->texture_id = texture.texture_id;
	}

	Texture(Logger* logger, std::string filename="default.jpg") {
		const char* file = filename.c_str();
		int width, height, nrChannels;
		this->logger = logger;
		this->data = stbi_load(file, &width, &height, &nrChannels, 0);
		logger->Log("Image Loaded");

		glGenTextures(1, &this->texture_id);
		logger->Log("Generated Texture ID");
		glBindTexture(GL_TEXTURE_2D, this->texture_id);
		fprintf(stdout, "TEXTID for %s: %d\n", filename.c_str(), this->texture_id);
		logger->Log("Binded Texture ID");
		if (this->data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			logger->Log("Generated Mipmap");
		}
		else {
			logger->Log("Failed to load texture", true);
			throw "Failed to load texture";
		}
		stbi_image_free(this->data);
		this->logger->Log("Removed Image Data");

	}

	void Draw(unsigned int unit) {
		if (unit < 0 || unit > 31) {
			logger->Log("Unit is outside of acceptable range", true);
			throw "Unit is outside of acceptable range";
		}

		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, this->texture_id);
	}

	void ClearGPUMemory() {
		glActiveTexture(GL_TEXTURE0);
		glDeleteTextures(1, &this->texture_id);
		logger->Log("Removed Texture Data (FROM TEXTURE CLASS)");
	}

	~Texture() {
		ClearGPUMemory();
		logger->Log("Removed Texture Data (FROM TEXTURE CLASS)");
	}

	Logger* logger;
	unsigned char* data;
	unsigned int texture_id;
};

#endif