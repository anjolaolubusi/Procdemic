#ifndef OBJECTS_H
#define OBJECTS_H

#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>

struct LightSource {
public:
	Transform transform;
	Mesh* mesh;
	Texture* texture;
	glm::vec3 Light;
	Logger* logger;

	LightSource(Vertex* vert, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, std::string textureImage, Logger* logger) {
		this->mesh = new Mesh(vert, NumberOfVertices, indices, numIndices, logger);
		this->texture = new Texture(logger, textureImage);
		this->Light = glm::vec3(1.0f, 1.0f, 1.0f);
		this->logger = logger;

	}

	void Draw(Shader* shader, Camera& cam) {
		shader->Use();
		texture->Draw(0);
		shader->Update(transform, cam);
		this->mesh->Draw(shader->shaderProgram);
	}


	~LightSource() {
		logger->Log("Clearing LightSoruce");
		free(mesh);
		texture->ClearGPUMemory();
		free(texture);
		logger->Log("Cleared LightSoruce");

	}
};

struct WorldObjectManager {
public:
	std::vector<Transform> trans_list;
	std::vector<Mesh> mesh_list;
	std::vector<Texture*> texture_list;
	std::vector<glm::vec3> color_list;
	
	int total_num;
	Logger* logger = NULL;
	LightSource* ls = NULL;

	WorldObjectManager(Logger* logger) {
		total_num = -1;
		this->logger = logger;
		ls = NULL;
	}

	void Draw(Shader* shader, Camera& cam) {
		for (int i = 0; i < total_num; i++) {
			glm::vec3 lightDir = glm::normalize(ls->transform.pos - trans_list.at(i).pos);
			shader->Use();
			texture_list.at(i)->Draw(0);
			shader->Update(trans_list.at(i), cam);
			glm::mat4 normalMatrix = glm::transpose(glm::inverse(trans_list.at(i).model));
			glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "normalMatrix"), 1, false, &normalMatrix[0][0]);
			glUniform3fv(glGetUniformLocation(shader->shaderProgram, "ourColor"), 1, &color_list.at(i)[0]);
			glUniform3fv(glGetUniformLocation(shader->shaderProgram, "lightcolor"), 1, &ls->Light[0]);
			glUniform3fv(glGetUniformLocation(shader->shaderProgram, "lightDir"), 1, &lightDir[0]);
			mesh_list.at(i).Draw(shader->shaderProgram);
		}
	}

	void Add(Vertex* vert, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, std::string textureImage, LightSource* lights, Logger* logger) {
		trans_list.push_back(Transform(glm::vec3(15.0f, 0.0f, -2.0f)));
		mesh_list.push_back(Mesh(vert, NumberOfVertices, indices, numIndices, logger));
		texture_list.push_back(new Texture(logger, textureImage));
		color_list.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		logger->Log("Added Entity to arrays");
		total_num = trans_list.size();
		ls = lights;
	}

	void Update() {
		for (int i = 0; i < total_num; i++) {
			trans_list.at(i).GetRot()->y = sin(glfwGetTime() * (M_PI / 180)) * 100;
		}
	}

	~WorldObjectManager() {
		for (int i = 0; i < total_num; i++) {
			texture_list.at(i)->ClearGPUMemory();
			free(texture_list.at(i));
			logger->Log("Freed texture");
		}
	}
};

#endif