#include "Texture.h"

Texture::Texture(const char* file, Logger* logger) {
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	glGenTextures(1, &this->texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		logger->Log("Failed to load texture", true);
		throw "Failed to load texture";
	}
	stbi_image_free(data);
}