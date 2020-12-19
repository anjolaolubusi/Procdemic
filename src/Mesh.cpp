#include "Mesh.h"

Mesh::Mesh() {

}

Mesh::Mesh(const Mesh& mesh) {
	this->logger = mesh.logger;
	this->VAO = mesh.VAO;
	this->VBO = mesh.VBO;
}

//Mesh constructor
Mesh::Mesh(Vertex* vert, size_t NumberOfVertices, Logger* logger) {
	this->logger = logger;
	glGenVertexArrays(1, &this->VAO);
	this->logger->Log("Generated Vertex Array");
    glGenBuffers(1, &this->VBO);
	this->logger->Log("Generated Vertex Buffer Array");

	glBindVertexArray(this->VAO);
	this->logger->Log("Binding Vertex Array Object");
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	this->logger->Log("Binding Vertex Buffer Array");
    glBufferData(GL_ARRAY_BUFFER, NumberOfVertices * sizeof(Vertex), &vert[0], GL_STATIC_DRAW);
	this->logger->Log("Sending Vertex Data To Array");

	for (int i = 0; i < NUM_BUFFERS; i++) {
		switch (i) {
			case POS:
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
				glEnableVertexAttribArray(0);
				this->logger->Log("Position Data Bounds Are Determined");
				break;
			case COLORS:
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
				glEnableVertexAttribArray(1);
				this->logger->Log("Colour Data Bounds Are Determined");
				break;
			case TEXTURES:
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)( 2 * sizeof(glm::vec3)));
				glEnableVertexAttribArray(2);
				this->logger->Log("Texture Data Bounds Are Determined");
				break;
		}
	}

	glBindVertexArray(this->VAO);
}

//Draws the mesh
void Mesh::Draw(unsigned int shaderProgram){
	glUseProgram(shaderProgram);
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

//Mesh Destructor
Mesh::~Mesh() {
	glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
	this->logger->Log("Buffers and Vertex Arrays Are Deleted");
}
