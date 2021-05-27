#ifndef OBJECTS_H
#define OBJECTS_H

#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include "VertexManager.h"

struct LightObjectManager{
public:
	std::vector<Transform> trans_list;
	std::vector<Mesh*> mesh_list;
    std::string texture_use;

	int total_num;
	Logger* logger = NULL;

	LightObjectManager(Logger* logger) {
		total_num = -1;
		this->logger = logger;
	}

	void Draw(Shader* shader, Camera& cam, TextureManager& textManager) {
		shader->Use();
		for (int i = 0; i < total_num; i++) {
            textManager.Draw(texture_use);
			shader->setMat4("transform", trans_list.at(i).GetModel());
			shader->setMat4("camera", cam.cameraMatrix());
			mesh_list.at(i)->Draw(shader->shaderProgram);
		}
	}

	void Add(VertexManager vert, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, std::string textureImage, Logger* logger) {
		trans_list.push_back(Transform());
		mesh_list.push_back(new Mesh(vert, NumberOfVertices, indices, numIndices, logger));
		texture_use = textureImage;
		logger->Log("Added Entity to arrays");
		total_num = trans_list.size();
	}

	void Update() {
		for (int i = 0; i < total_num; i++) {
			trans_list.at(i).GetPos()->z = -7;
			trans_list.at(i).GetPos()->y = 7;
		}
	}

	~LightObjectManager() {
		for (int i = 0; i < total_num; i++) {
			mesh_list.at(i)->ClearGPUMemory();
			free(mesh_list.at(i));
			logger->Log("Freed texture");
		}
	}
};

struct WorldObjectManager {
public:
	std::vector<Transform> trans_list;
	std::vector<Mesh*> mesh_list;
    std::string texture_use;

	int total_num;
	Logger* logger = NULL;

	WorldObjectManager(Logger* logger) {
		total_num = -1;
		this->logger = logger;
	}

	void Draw(Shader* shader, Camera& cam, TextureManager& textManager, Transform& lightPos) {
		shader->Use();
		for (int i = 0; i < total_num; i++) {
            textManager.Draw(texture_use);
			shader->setMat4("transform", trans_list.at(i).GetModel());
			shader->setMat4("camera", cam.cameraMatrix());
			shader->setVec3("lightPos", lightPos.pos);
            shader->setVec3("lightColour", 1, 1, 1);
            shader->setMat4("inv_model", glm::transpose(glm::inverse(trans_list.at(i).GetModel())));
            shader->setVec3("viewPos", lightPos.pos);
			mesh_list.at(i)->Draw(shader->shaderProgram);
		}
	}

	void Add(VertexManager vert, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, std::string textureImage, Logger* logger) {
		trans_list.push_back(Transform());
		mesh_list.push_back(new Mesh(vert, NumberOfVertices, indices, numIndices, logger));
		texture_use = textureImage;
		logger->Log("Added Entity to arrays");
		total_num = trans_list.size();
	}

	void Update() {
		for (int i = 0; i < total_num; i++) {
			trans_list.at(i).GetPos()->z = -7;
			trans_list.at(i).GetPos()->y = 2;
			trans_list.at(i).GetScale()->x = 50;
			trans_list.at(i).GetScale()->z = 30;

		}
	}

	~WorldObjectManager() {
		for (int i = 0; i < total_num; i++) {
			mesh_list.at(i)->ClearGPUMemory();
			free(mesh_list.at(i));
			logger->Log("Freed texture");
		}
	}
};

#endif
