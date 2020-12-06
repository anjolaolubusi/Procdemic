#include "Mesh.h"

Mesh::Mesh(Vertex* vert, Logger* logger) {
	this->logger = logger;
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	glGenBuffers(NUM_BUFFERS, this->VBO);

	for(int i = 0; i < NUM_BUFFERS; i++){
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vert->data), vert->data, GL_STATIC_DRAW);
        switch(i){
        case POS:
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
            glEnableVertexAttribArray(0);
        case COLORS:
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
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
    glDeleteBuffers(2, this->VBO);

}
