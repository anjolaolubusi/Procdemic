#include "Mesh.h"

Mesh::Mesh(Vertex* vert, Logger* logger) {
	this->logger = logger;
	glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex), &vert[0], GL_STATIC_DRAW);

	for (int i = 0; i < NUM_BUFFERS; i++) {
		switch (i) {
			case POS:
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
				glEnableVertexAttribArray(0);
				break;
			case COLORS:
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
				glEnableVertexAttribArray(1);
				break;
		}
	}

}

void Mesh::Draw(unsigned int shaderProgram){
	glUseProgram(shaderProgram);
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


Mesh::~Mesh() {
	glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);

}
