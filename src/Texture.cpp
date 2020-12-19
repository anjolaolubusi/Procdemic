#include "Texture.h"

//Construtor
Texture::Texture(const char* file, Logger* logger) {
	int width, height, nrChannels;
	this->logger = logger;
	this->data = stbi_load(file, &width, &height, &nrChannels, 0);
	logger->Log("Image Loaded");

	glGenTextures(1, &this->texture_id);
	logger->Log("Generated Texture ID");
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
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

//Draws the texture
void Texture::Draw(unsigned int unit) {
	if (unit < 0 || unit > 31) {
		logger->Log("Unit is outside of acceptable range", true);
		throw "Unit is outside of acceptable range";
	}

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
}

//Deletes the Texture
Texture::~Texture() {
	glDeleteTextures(1, &this->texture_id);
}