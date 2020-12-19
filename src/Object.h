#ifndef OBJECT_H
#define OBJECT_H
#include "Transform.h"
#include "Mesh.h"

struct Object {
public:
	Transform transform;
	Mesh mesh;
//	Texture texture;
	Object() {
	
	}

	Object(Mesh mesh, Texture texture) {
		this->mesh = mesh;
		//this->texture = texture;
	}

	void Draw(unsigned int shaderProgram) {
		this->mesh.Draw(shaderProgram);
	//	this->texture.Draw(0);
	}
};

#endif