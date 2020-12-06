#ifndef MESH_H
#define MESH_H
#include "Logger.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

struct Vertex{
    /*float data[18] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };*/

    glm::vec3 pos;
    glm::vec3 color;

    Vertex(glm::vec3 pos, glm::vec3 color) {
        this->pos = pos;
        this->color = color;
    }

};

class Mesh
{
public:
	Mesh(Vertex* vert, Logger* logger);
    Logger* logger;
    unsigned int VAO;
    enum VertexAttribute{POS, COLORS, NUM_BUFFERS};
    unsigned int VBO;
    void Draw(unsigned int shaderProgram);
    ~Mesh();

};
#endif
