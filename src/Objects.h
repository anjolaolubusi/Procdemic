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

struct WorldObjectManager {
public:
	std::vector<Transform> trans_list;
	std::vector<Mesh*> mesh_list;
	std::vector<Texture*> texture_list;
	
	int total_num;
	Logger* logger = NULL;

	WorldObjectManager(Logger* logger) {
		total_num = -1;
		this->logger = logger;
	}

	void Draw(Shader* shader, Camera& cam) {
		shader->Use();
		for (int i = 0; i < total_num; i++) {
			texture_list.at(i)->Draw(0);
			shader->Update(trans_list.at(i), cam);
			mesh_list.at(i)->Draw(shader->shaderProgram);
		}
	}

	void Add(VertexManager vert, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, std::string textureImage, Logger* logger) {
		trans_list.push_back(Transform());
		mesh_list.push_back(new Mesh(vert, NumberOfVertices, indices, numIndices, logger));
		texture_list.push_back(new Texture(logger, textureImage));
		logger->Log("Added Entity to arrays");
		total_num = trans_list.size();
	}

	void Update() {
		for (int i = 0; i < total_num; i++) {
			trans_list.at(i).GetPos()->z = -2;
		}
	}

	~WorldObjectManager() {
		for (int i = 0; i < total_num; i++) {
			mesh_list.at(i)->ClearGPUMemory();
			texture_list.at(i)->ClearGPUMemory();
			free(texture_list.at(i));
			free(mesh_list.at(i));
			logger->Log("Freed texture");
		}
	}
};

#endif