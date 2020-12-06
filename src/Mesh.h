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

    float data[6];

    Vertex(glm::vec3 pos, glm::vec3 color){
        for(int i = 0; i < 6; i++){
            if(i < 3){
                data[i] = pos[i];
            }else if(i < 6){
                data[i] = color[i - 3];
            }
        }
    }

};

class Mesh
{
public:
	Mesh(Vertex* vert, Logger* logger);
    Logger* logger;
    unsigned int VAO;
    enum VertexAttribute{POS, COLORS, NUM_BUFFERS};
    unsigned int VBO[NUM_BUFFERS];
    void Draw(unsigned int shaderProgram);
    ~Mesh();

};
#endif
