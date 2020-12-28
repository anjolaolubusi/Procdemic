#ifndef OBJECT_H
#define OBJECT_H
#include "Transform.h"
#include "Mesh.h"

struct Object {
public:
	Transform transform;
	Mesh* mesh;
	Texture texture;
	Object() {
	
	}

	Object(Vertex* vert, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, Texture& texture, Logger* logger) {
		this->mesh = new Mesh(vert, NumberOfVertices, indices, numIndices, logger);
		this->texture = texture;
	}

	void Draw(unsigned int shaderProgram) {
		this->mesh->Draw(shaderProgram);
		this->texture.Draw(0);
	}

	~Object() {
		free(mesh);
	}
};

#endif