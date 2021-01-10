#ifndef OBJECTS_H
#define OBJECTS_H

#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

struct LightSource {
public:
	Transform transform;
	Mesh* mesh;
	Texture* texture;
	glm::vec3 Light;


	LightSource(Vertex* vert, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, std::string textureImage, Logger* logger) {
		this->mesh = new Mesh(vert, NumberOfVertices, indices, numIndices, logger);
		this->texture = new Texture(logger, textureImage);
		this->Light = glm::vec3(1.0f, 1.0f, 1.0f);

	}

	void Draw(Shader* shader, Camera& cam) {
		shader->Use();
		texture->Draw(0);
		shader->Update(transform, cam);
		this->mesh->Draw(shader->shaderProgram);
	}


	~LightSource() {
		free(mesh);
		free(texture);

	}
};

struct WorldObject {
public:
	Transform transform;
	Mesh* mesh;
	Texture* texture;
	glm::vec3 ourColor;

	WorldObject(Vertex* vert, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, std::string textureImage, Logger* logger) {
		this->mesh = new Mesh(vert, NumberOfVertices, indices, numIndices, logger);
		this->texture = new Texture(logger, textureImage);
		this->ourColor = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	void Draw(Shader* shader, Camera& cam, LightSource& ls) {
		glm::vec3 lightDir = glm::normalize(ls.transform.pos - transform.pos);
		shader->Use();
		texture->Draw(0);
		shader->Update(transform, cam);
		glm::mat4 normalMatrix = glm::transpose(glm::inverse(transform.model));
		glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "normalMatrix"), 1, false, &normalMatrix[0][0]);
		glUniform3fv(glGetUniformLocation(shader->shaderProgram, "ourColor"), 1, &this->ourColor[0]);
		glUniform3fv(glGetUniformLocation(shader->shaderProgram, "lightcolor"), 1, &ls.Light[0]);
		glUniform3fv(glGetUniformLocation(shader->shaderProgram, "lightDir"), 1, &lightDir[0]);

		this->mesh->Draw(shader->shaderProgram);
	}

	~WorldObject() {
		free(mesh);
		free(texture);
	}
};


#endif