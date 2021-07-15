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
#include "math.h"
#include <GLFW/glfw3.h>

#define PI 3.14159265


struct LightObjectManager{
public:
	std::vector<Transform> trans_list;
	std::vector<Mesh*> mesh_list;
	std::vector<std::string> textures_list;
	std::vector<glm::vec3> object_color_list;
	std::vector<float> ambient_list;
	std::vector<float> specular_list;
	std::vector<float> diffuse_list;

	int total_num;
	Logger* logger = NULL;

	LightObjectManager(Logger* logger) {
		total_num = -1;
		this->logger = logger;
	}

	void Draw(Shader* shader, Camera& cam, TextureManager& textManager) {
		shader->Use();
		for (int i = 0; i < total_num; i++) {
            textManager.Draw(textures_list.at(i));
			shader->setMat4("transform", trans_list.at(i).GetModel());
			shader->setMat4("camera", cam.cameraMatrix());
			shader->setVec3("obj_Color", object_color_list.at(i));
			mesh_list.at(i)->Draw(shader->shaderProgram);
		}
	}

	void Add(VertexManager vert, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, std::string textureImage, glm::vec3 obj_color, Logger* logger, float ambient=0.2f, float specular=1.0f, float diffuse=0.5f) {
		trans_list.push_back(Transform());
		mesh_list.push_back(new Mesh(vert, NumberOfVertices, indices, numIndices, logger));
		textures_list.push_back(textureImage);
		object_color_list.push_back(obj_color);
		ambient_list.push_back(ambient);
		specular_list.push_back(specular);
		diffuse_list.push_back(diffuse);
		logger->Log("Added Entity to arrays");
		total_num = trans_list.size();
	}

	void Add(VertexManager vert, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, std::string textureImage, glm::vec3 obj_color, float ambient, float specular, float diffuse, Logger* logger) {
		trans_list.push_back(Transform());
		mesh_list.push_back(new Mesh(vert, NumberOfVertices, indices, numIndices, logger));
		textures_list.push_back(textureImage);
		object_color_list.push_back(obj_color);
		ambient_list.push_back(ambient);
		specular_list.push_back(specular);
		diffuse_list.push_back(diffuse);
		logger->Log("Added Entity to arrays");
		total_num = trans_list.size();
	}

	void Update() {

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
	std::vector<glm::vec3> object_color_list;
	std::vector<std::string> textures_list;
    std::vector<std::string> specular_tex_list;

	int total_num;
	Logger* logger = NULL;

	WorldObjectManager(Logger* logger) {
		total_num = -1;
		this->logger = logger;
	}

	void Draw(Shader* shader, Camera& cam, TextureManager& textManager, glm::vec3& lightPos, glm::vec3 lightColor, float ambient=0.2f, float diffuse=0.5f, float specular=1.0f) {
		shader->Use();
		for (int i = 0; i < total_num; i++) {
            shader->setInt("material.diffuse", textManager.GetTextureId(textures_list.at(i)) - 1);
            shader->setInt("material.specular", textManager.GetTextureId(specular_tex_list.at(i)) - 1);
			shader->setMat4("transform", trans_list.at(i).GetModel());
			shader->setMat4("camera", cam.cameraMatrix());
			shader->setVec3("light.direction", 1.0f, -2.0f, 1.0f);
            shader->setVec3("light.color", lightColor);
            shader->setMat4("inv_model", glm::transpose(glm::inverse(trans_list.at(i).GetModel())));
            shader->setVec3("viewPos", lightPos);
            shader->setVec3("obj_Color", object_color_list.at(i));
            shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
            shader->setFloat("material.shininess", 64.0f);
            shader->setVec3("light.ambient", glm::vec3(ambient));
            shader->setVec3("light.diffuse", glm::vec3(diffuse));
            shader->setVec3("light.specular", glm::vec3(specular));
            shader->setFloat("light.constant",  1.0f);
            shader->setFloat("light.linear",    0.045f);
            shader->setFloat("light.quadratic", 0.0075f);
            textManager.Draw(textures_list.at(i));
            textManager.Draw(specular_tex_list.at(i));
			mesh_list.at(i)->Draw(shader->shaderProgram);
		}
	}

	void Add(VertexManager vert, size_t NumberOfVertices, unsigned int* indices, unsigned int numIndices, std::string textureImage, std::string specImage, glm::vec3 obj_color, glm::vec3 _pos, Logger* logger) {
		trans_list.push_back(Transform());
		trans_list.back().pos = _pos;
		mesh_list.push_back(new Mesh(vert, NumberOfVertices, indices, numIndices, logger));
		textures_list.push_back(textureImage);
		object_color_list.push_back(obj_color);
        specular_tex_list.push_back(specImage);
		logger->Log("Added Entity to arrays");
		total_num = trans_list.size();
	}

	void Update() {

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
