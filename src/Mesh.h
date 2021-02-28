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
    glm::vec2 tex;
    glm::vec3 norm;

    Vertex(glm::vec3 pos, glm::vec2 tex, glm::vec3 norm) {
        this->pos = pos;
        this->tex = tex;
        this->norm = glm::normalize(norm);
    }

};

struct Mesh
{
    Mesh(Vertex* vert, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, Logger* logger) {
		this->logger = logger;
		this->NumOfIndices = numIndices;
		glGenVertexArrays(1, &this->VAO);
		this->logger->Log("Generated Vertex Array");
		glGenBuffers(NUM_BUFFERS, this->VBO);
		this->logger->Log("Generated Vertex Buffer Array");

		glBindVertexArray(this->VAO);

		for (int i = 0; i < NUM_BUFFERS; i++) {
			switch (i) {
			case POS:
				glBindBuffer(GL_ARRAY_BUFFER, this->VBO[POS]);
				this->logger->Log("Binding Vertex Buffer Array");
				glBufferData(GL_ARRAY_BUFFER, NumberOfVertices * sizeof(vert[0]), &vert[0], GL_STATIC_DRAW);
				this->logger->Log("Sending Vertex Data To Array");
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vert[0]), (void*)(0));
				glEnableVertexAttribArray(0);
				this->logger->Log("Position Data Bounds Are Determined");
				break;
			case TEXTURES:
				glBindBuffer(GL_ARRAY_BUFFER, this->VBO[TEXTURES]);
				this->logger->Log("Binding Vertex Buffer Array");
				glBufferData(GL_ARRAY_BUFFER, NumberOfVertices * sizeof(vert[0]), &vert[0], GL_STATIC_DRAW);
				this->logger->Log("Sending Vertex Data To Array");
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vert[0]), (void*)(sizeof(glm::vec3)));
				glEnableVertexAttribArray(1);
				this->logger->Log("Texture Data Bounds Are Determined");
				break;
			case INDEX:
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->VBO[INDEX]);
				this->logger->Log("Binding Indices Buffer Array");
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
				break;
			case NORMAL:
				glBindBuffer(GL_ARRAY_BUFFER, this->VBO[NORMAL]);
				this->logger->Log("Binding Normals Buffer Array");
				glBufferData(GL_ARRAY_BUFFER, NumberOfVertices * sizeof(vert[0]), &vert[0], GL_STATIC_DRAW);
				this->logger->Log("Sending Normals Data To Array");
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(vert[0]), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
				glEnableVertexAttribArray(2);
				this->logger->Log("Normal Data Bounds Are Determined");
				break;
			}
		}

		glBindVertexArray(this->VAO);
	}
    Logger* logger;
    unsigned int VAO;
    enum BUFFERS{POS, TEXTURES, INDEX, NORMAL, NUM_BUFFERS};
    unsigned int VBO[NUM_BUFFERS];
	void Draw(unsigned int shaderProgram) {
		glUseProgram(shaderProgram);
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, NumOfIndices, GL_UNSIGNED_INT, 0);
	}
    unsigned int NumOfIndices;
    ~Mesh() {
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(NUM_BUFFERS, this->VBO);
		this->logger->Log("Buffers and Vertex Arrays Are Deleted");
	}

};

#endif
