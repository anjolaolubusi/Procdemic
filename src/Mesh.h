#ifndef MESH_H
#define MESH_H
#include "Logger.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Texture.h"

struct Vertex{
    /*float data[18] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };*/

    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 tex;

    Vertex(glm::vec3 pos, glm::vec3 color, glm::vec2 tex) {
        this->pos = pos;
        this->color = color;
        this->tex = tex;
    }

};

class Mesh
{
public:
	Mesh(Vertex* vert, Logger* logger);
    Logger* logger;
    unsigned int VAO;
    enum VertexAttribute{POS, COLORS, TEXTURES, NUM_BUFFERS};
    unsigned int VBO;
    unsigned int textID;
    void Draw(unsigned int shaderProgram, unsigned int texture);
    ~Mesh();

};
#endif
