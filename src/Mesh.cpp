#include "Mesh.h"

//Mesh constructor
Mesh::Mesh(Vertex* vert, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, Logger* logger) {
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
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vert[0]), (void*)( sizeof(glm::vec3)));
				glEnableVertexAttribArray(1);
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
}

//Draws the mesh
void Mesh::Draw(unsigned int shaderProgram){
	glUseProgram(shaderProgram);
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, NumOfIndices, GL_UNSIGNED_INT, 0);
}

//Mesh Destructor
Mesh::~Mesh() {
	glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(NUM_BUFFERS, this->VBO);
	this->logger->Log("Buffers and Vertex Arrays Are Deleted");
}
