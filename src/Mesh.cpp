#include "Mesh.h"

Mesh::Mesh(Logger* logger) {
	this->logger = logger;
	glGenBuffers(1, &this->VAO);
	glGenVertexArrays(1, &this->VBO);
	this->logger->Log("Generating VBO ID");
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	this->logger->Log("Binding VBO ID To GL_ARRAY_BUFFER Object");
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
	this->logger->Log("Copy vertex data into array buffer");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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
