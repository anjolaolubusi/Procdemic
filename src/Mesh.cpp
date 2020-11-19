#include "Mesh.h"

Mesh::Mesh(Logger* logger) {
	this->logger = logger;
	glGenBuffers(1, &this->VBO);
	this->logger->Log("Generating VBO ID");
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	this->logger->Log("Binding VBO ID To GL_ARRAY_BUFFER Object");
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
	this->logger->Log("Copy vertex data into array buffer");
}