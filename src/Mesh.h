#ifndef MESH_H
#define MESH_H
#include "Logger.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

struct Vertex{
    glm::vec3 pos;
};

class Mesh
{
public:
	Mesh(Logger* logger);
    Logger* logger;
    float vertices[18] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    unsigned int VAO;
    unsigned int VBO;
    void Draw(unsigned int shaderProgram);
    ~Mesh();

};
#endif
