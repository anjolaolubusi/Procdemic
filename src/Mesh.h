#ifndef MESH_H
#define MESH_H
#include "Logger.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Texture.h"
#include <vector>
#include "VertexManager.h"

struct Mesh
{
	Mesh(VertexManager vertManage, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, Logger* logger) {
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
				printf("OPENGL ERROR for Binding Vertex Buffer: %i\n", glGetError());
				glBufferData(GL_ARRAY_BUFFER, NumberOfVertices * sizeof(glm::vec3), vertManage.pos_list.data(), GL_STATIC_DRAW);
				this->logger->Log("Sending Vertex Data To Array");
				printf("OPENGL ERROR for Sending Vertex Data: %i\n", glGetError());
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
				printf("OPENGL ERROR for Attrib Pointer Data: %i\n", glGetError());
				glEnableVertexAttribArray(0);
				this->logger->Log("Position Data Bounds Are Determined");
				printf("OPENGL ERROR for Enable Attrib Pointer Data: %i\n", glGetError());
				break;
			case TEXTURES:
				glBindBuffer(GL_ARRAY_BUFFER, this->VBO[TEXTURES]);
				this->logger->Log("Binding Vertex Buffer Array");
				printf("OPENGL ERROR for Binding Vertex Buffer: %i\n", glGetError());
				glBufferData(GL_ARRAY_BUFFER, NumberOfVertices * sizeof(GLfloat), vertManage.tex_list.data(), GL_STATIC_DRAW);
				this->logger->Log("Sending Vertex Data To Array");
				printf("OPENGL ERROR for Sending Vertex Data: %i\n", glGetError());
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0));
				printf("OPENGL ERROR for Attrib Pointer Data: %i\n", glGetError());
				glEnableVertexAttribArray(1);
				printf("OPENGL ERROR for Enable Attrib Pointer Data: %i\n", glGetError());
				this->logger->Log("Texture Data Bounds Are Determined");
				break;
			case INDEX:
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->VBO[INDEX]);
				this->logger->Log("Binding Indices Buffer Array");
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
				break;
			}
		}

		glBindVertexArray(this->VAO);
		printf("OPENGL ERROR for Final Bind Attrib Pointer Data: %i\n", glGetError());

	}


	Logger* logger;
    unsigned int VAO;
    enum BUFFERS{POS, TEXTURES, INDEX, NUM_BUFFERS};
    unsigned int VBO[NUM_BUFFERS];
	void Draw(unsigned int shaderProgram) {
		glUseProgram(shaderProgram);
		printf("OPENGL ERROR for Using Shader: %i\n", glGetError());
		glBindVertexArray(VAO);
		printf("OPENGL ERROR for Using Binding Vertex Array: %i\n", glGetError());
		glDrawElements(GL_TRIANGLES, NumOfIndices, GL_UNSIGNED_INT, 0);
		printf("OPENGL ERROR for Drawing Elements: %i\n", glGetError());
	}
    
	unsigned int NumOfIndices;
	
	void ClearGPUMemory() {
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(NUM_BUFFERS, this->VBO);
		this->logger->Log("Buffers and Vertex Arrays Are Deleted");
	}

    ~Mesh() {
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(NUM_BUFFERS, this->VBO);
		this->logger->Log("Buffers and Vertex Arrays Are Deleted (DEST)");
	}

};

#endif
