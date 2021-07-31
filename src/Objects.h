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
#include <string>

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

struct DirectionalLightManager{
public:
    std::vector<glm::vec3> direction_list;
    std::vector<glm::vec3> color_list;
    std::vector<glm::vec3> ambient_list;
    std::vector<glm::vec3> diffuse_list;
    std::vector<glm::vec3> specular_list;
    std::vector<bool> isOn_list;

    int total_num;
    Logger* logger = NULL;

    DirectionalLightManager(Logger* logger){
        total_num = -1;
        this->logger = logger;
    }

    void Add(glm::vec3 direction, glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, bool isOn){
        direction_list.push_back(direction);
        color_list.push_back(color);
        ambient_list.push_back(ambient);
        diffuse_list.push_back(diffuse);
        specular_list.push_back(specular);
        isOn_list.push_back(isOn);
        total_num = direction_list.size();
    }
};

struct PointLightManager{
public:
	std::vector<glm::vec3> pos_list;
	std::vector<glm::vec3> color_list;

	std::vector<glm::vec3> ambient_list;
	std::vector<glm::vec3> specular_list;
	std::vector<glm::vec3> diffuse_list;

    std::vector<float> constant_list;
	std::vector<float> linear_list;
	std::vector<float> quadratic_list;
    std::vector<bool> isOn_list;


	int total_num;
	Logger* logger = NULL;

	PointLightManager(Logger* logger) {
		total_num = -1;
		this->logger = logger;
	}

	void Add(glm::vec3 pos, glm::vec3 color, glm::vec3 ambient, glm::vec3 specular, glm::vec3 diffuse, float constant, float linear, float quadratic, bool isOn) {
		pos_list.push_back(pos);
		color_list.push_back(color);
		ambient_list.push_back(ambient);
		specular_list.push_back(specular);
		diffuse_list.push_back(diffuse);
		constant_list.push_back(constant);
		linear_list.push_back(linear);
		quadratic_list.push_back(quadratic);
		isOn_list.push_back(isOn);
		logger->Log("Added Entity to arrays");
		total_num = pos_list.size();
	}

	~PointLightManager() {

	}
};

struct SpotLightManager{
public:
	std::vector<glm::vec3> pos_list;
	std::vector<glm::vec3> direction_list;
    std::vector<float> cutOff_list;

	std::vector<glm::vec3> color_list;
	std::vector<glm::vec3> ambient_list;
	std::vector<glm::vec3> specular_list;
	std::vector<glm::vec3> diffuse_list;

    std::vector<float> constant_list;
	std::vector<float> linear_list;
	std::vector<float> quadratic_list;
    std::vector<bool> isOn_list;



	int total_num;
	Logger* logger = NULL;

	SpotLightManager(Logger* logger) {
		total_num = -1;
		this->logger = logger;
	}

	void Add(glm::vec3 pos, glm::vec3 dir, float cutOff, glm::vec3 color, glm::vec3 ambient, glm::vec3 specular, glm::vec3 diffuse, float constant, float linear, float quadratic, bool isOn) {
		pos_list.push_back(pos);
		direction_list.push_back(dir);
		cutOff_list.push_back(cutOff);
		color_list.push_back(color);
		ambient_list.push_back(ambient);
		specular_list.push_back(specular);
		diffuse_list.push_back(diffuse);
		constant_list.push_back(constant);
		linear_list.push_back(linear);
		quadratic_list.push_back(quadratic);
		isOn_list.push_back(isOn);
		logger->Log("Added Entity to arrays");
		total_num = pos_list.size();
	}

	~SpotLightManager() {

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

	void Draw(Shader* shader, Camera& cam, TextureManager& textManager, DirectionalLightManager& dirLightManager, PointLightManager& pointLightManager, SpotLightManager& spotLightManager) {
		shader->Use();
		for (int i = 0; i < total_num; i++) {
            shader->setInt("material.diffuse", textManager.GetTextureId(textures_list.at(i)) - 1);
            shader->setInt("material.specular", textManager.GetTextureId(specular_tex_list.at(i)) - 1);
			shader->setMat4("transform", trans_list.at(i).GetModel());
			shader->setMat4("camera", cam.cameraMatrix());
            shader->setMat4("inv_model", glm::transpose(glm::inverse(trans_list.at(i).GetModel())));
            shader->setVec3("viewPos", cam.cameraPos);
            shader->setVec3("obj_Color", object_color_list.at(i));
            //shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
            shader->setFloat("material.shininess", 64.0f);

            if(dirLightManager.total_num > 0){
                shader->setBool("hasDirLight", true);
            }
            if(pointLightManager.total_num > 0){
                shader->setBool("hasPointLight", true);
            }
            if(spotLightManager.total_num > 0){
                shader->setBool("hasSpotLight", true);
            }

            for(int i = 0; i < dirLightManager.total_num; i++){
                std::string gsl_code = "dirlight.";
                shader->setVec3((gsl_code + "direction").c_str(), dirLightManager.direction_list.at(i));
                shader->setVec3((gsl_code + "color").c_str(), dirLightManager.color_list.at(i));
                shader->setVec3((gsl_code + "ambient").c_str(), dirLightManager.ambient_list.at(i));
                shader->setVec3((gsl_code + "diffuse").c_str(), dirLightManager.diffuse_list.at(i));
                shader->setVec3((gsl_code + "specular").c_str(), dirLightManager.specular_list.at(i));
                shader->setBool((gsl_code + "isOn").c_str(), dirLightManager.isOn_list.at(i));
            }


            for(int i = 0; i < pointLightManager.total_num; i++){
                std::string gsl_code = "pointLight[" + std::to_string(i) + "].";
                shader->setVec3((gsl_code + "position").c_str(), pointLightManager.pos_list.at(i));
                shader->setVec3((gsl_code + "color").c_str(), pointLightManager.color_list.at(i));
                shader->setVec3((gsl_code + "ambient").c_str(), pointLightManager.ambient_list.at(i));
                shader->setVec3((gsl_code + "diffuse").c_str(), pointLightManager.diffuse_list.at(i));
                shader->setVec3((gsl_code + "specular").c_str(), pointLightManager.specular_list.at(i));
                shader->setFloat((gsl_code + "constant").c_str(), pointLightManager.constant_list.at(i));
                shader->setFloat((gsl_code + "linear").c_str(), pointLightManager.linear_list.at(i));
                shader->setFloat((gsl_code + "quadratic").c_str(), pointLightManager.quadratic_list.at(i));
                shader->setBool((gsl_code + "isOn").c_str(), dirLightManager.isOn_list.at(i));
            }

            for(int i = 0; i < spotLightManager.total_num; i++){
                std::string gsl_code = "spotLight[" + std::to_string(i) + "].";
                shader->setVec3((gsl_code + "position").c_str(), spotLightManager.pos_list.at(i));
                shader->setVec3((gsl_code + "direction").c_str(), spotLightManager.direction_list.at(i));
                shader->setFloat((gsl_code + "cutOff").c_str(), spotLightManager.cutOff_list.at(i));
                shader->setVec3((gsl_code + "color").c_str(), spotLightManager.color_list.at(i));
                shader->setVec3((gsl_code + "ambient").c_str(), spotLightManager.ambient_list.at(i));
                shader->setVec3((gsl_code + "diffuse").c_str(), spotLightManager.diffuse_list.at(i));
                shader->setVec3((gsl_code + "specular").c_str(), spotLightManager.specular_list.at(i));
                shader->setFloat((gsl_code + "constant").c_str(), spotLightManager.constant_list.at(i));
                shader->setFloat((gsl_code + "linear").c_str(), spotLightManager.linear_list.at(i));
                shader->setFloat((gsl_code + "quadratic").c_str(), spotLightManager.quadratic_list.at(i));
                shader->setBool((gsl_code + "isOn").c_str(), dirLightManager.isOn_list.at(i));
            }

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
