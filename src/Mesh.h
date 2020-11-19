#ifndef MESH_H
#define MESH_H
#include "Logger.h"
#include <glad/glad.h>

class Mesh
{
	Mesh(Logger* logger);
    Logger* logger;
    float vertices[9] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };
    unsigned int VBO;
};
#endif
