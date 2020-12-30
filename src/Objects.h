#ifndef OBJECTS_H
#define OBJECTS_H

#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"
#include <glm/glm.hpp>

struct WorldObject {
public:
	Transform transform;
	Mesh* mesh;
	Texture texture;
	glm::vec3 ourColor;
	glm::vec3 Light;

	WorldObject(Vertex* vert, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, Texture& texture, Logger* logger) {
		this->mesh = new Mesh(vert, NumberOfVertices, indices, numIndices, logger);
		this->texture = texture;
		this->ourColor = glm::vec3(1.0f, 1.0f, 1.0f);
		this->Light = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	void Draw(unsigned int shaderProgram) {
		this->mesh->Draw(shaderProgram);
		glUniform3fv(glGetUniformLocation(shaderProgram, "ourColor"), 1, &this->ourColor[0]);
		glUniform3fv(glGetUniformLocation(shaderProgram, "lightcolor"), 1, &this->Light[0]);
		this->texture.Draw(0);
	}

	~WorldObject() {
		free(mesh);
	}
};

struct LightSource {
public:
	Transform transform;
	Mesh* mesh;
	Texture texture;


	LightSource(Vertex* vert, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, Texture& texture, Logger* logger) {
		this->mesh = new Mesh(vert, NumberOfVertices, indices, numIndices, logger);
		this->texture = texture;
	}

	void Draw(unsigned int shaderProgram) {
		this->mesh->Draw(shaderProgram);
		this->texture.Draw(0);
	}

	~LightSource() {
		free(mesh);
	}
};

#endif