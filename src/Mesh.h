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

		//TODO: Abstract for loop
		for (int i = 0; i < NUM_BUFFERS; i++) {
			switch (i) {
			case POS:
				glBindBuffer(GL_ARRAY_BUFFER, this->VBO[POS]);
				this->logger->Log("Binding Vertex Buffer Array");
				glBufferData(GL_ARRAY_BUFFER, NumberOfVertices * sizeof(glm::vec3), vertManage.pos_list.data(), GL_STATIC_DRAW);
				CheckForOpenGLError();
				this->logger->Log("Sending Vertex Data To Array");
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
				CheckForOpenGLError();
				glEnableVertexAttribArray(0);
				this->logger->Log("Position Data Bounds Are Determined");
				break;
			case TEXTURES:
				glBindBuffer(GL_ARRAY_BUFFER, this->VBO[TEXTURES]);
				this->logger->Log("Binding Vertex Buffer Array");
				glBufferData(GL_ARRAY_BUFFER, NumberOfVertices * sizeof(glm::vec2), vertManage.tex_list.data(), GL_STATIC_DRAW);
				CheckForOpenGLError();
				this->logger->Log("Sending Vertex Data To Array");
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0));
				glEnableVertexAttribArray(1);
				this->logger->Log("Texture Data Bounds Are Determined");
				break;
			case INDEX:
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->VBO[INDEX]);
				this->logger->Log("Binding Indices Buffer Array");
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
				CheckForOpenGLError();
				break;
            case NORMAL:
                glBindBuffer(GL_ARRAY_BUFFER, this->VBO[NORMAL]);
				this->logger->Log("Binding Normal Buffer Array");
				glBufferData(GL_ARRAY_BUFFER, NumberOfVertices * sizeof(glm::vec3), vertManage.normal_list.data(), GL_STATIC_DRAW);
				CheckForOpenGLError();
				this->logger->Log("Sending Normal Data To Array");
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
				CheckForOpenGLError();
				glEnableVertexAttribArray(2);
				this->logger->Log("Normal Data Bounds Are Determined");
				break;
			}
		}

		glBindVertexArray(this->VAO);
		printf("OPENGL ERROR for Final Bind Attrib Pointer Data: %i\n", glGetError());

	}


	Logger* logger;
    unsigned int VAO;
    enum BUFFERS{POS, TEXTURES, INDEX, NORMAL, NUM_BUFFERS};
    unsigned int VBO[NUM_BUFFERS];
	void Draw(unsigned int shaderProgram) {
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, NumOfIndices, GL_UNSIGNED_INT, 0);
		CheckForOpenGLError();
	}

	unsigned int NumOfIndices;

	void CheckForOpenGLError() {
	    try{
            if (glGetError() != 0) {
                std::string err_msg = "OPENGL ERROR: " + std::to_string(glGetError());
                throw err_msg.c_str();
            }
	    }catch(const char* msg){
            logger->Log(msg, true);
	    }
	}

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
