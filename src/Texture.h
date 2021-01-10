#ifndef TEXTURE_H
#define TEXTURE_H
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Logger.h"
#include <stb_image/stb_image.h>

class Texture {
public:
	Texture(const Texture& texture);
	Texture(Logger* logger, std::string filename="default.jpg");
	void Draw(unsigned int unit);
	~Texture();

	Logger* logger;
	unsigned char* data;
	unsigned int texture_id;
};

#endif