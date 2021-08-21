#ifndef VERTEXMANAGER_H
#define VERTEXMANAGER_H
#include <glm/glm.hpp>
#include <vector>
#include "Logger.h"

struct VertexManager {
	std::vector<glm::vec3> pos_list;
	std::vector<glm::vec2> tex_list;
	int total_num;
	std::vector<unsigned int> indices;
    std::vector<glm::vec3> normal_list;

    //Adds Vertex to list
	void Add(glm::vec3 pos, glm::vec2 tex, glm::vec3 normal) {
		pos_list.push_back(pos);
		tex_list.push_back(tex);
		normal_list.push_back(normal);
		total_num = pos_list.size();
	}

	void Clear(){
        pos_list.clear();
        tex_list.clear();
        indices.clear();
        normal_list.clear();
	}

	void Add(glm::vec3 pos, glm::vec2 tex) {
		pos_list.push_back(pos);
		tex_list.push_back(tex);
		total_num = pos_list.size();
	}
	void SetIncides(){
		for (int i = 0; i < total_num; i = i + 4) {
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + 3);
			indices.push_back(i);
			indices.push_back(i + 2);
			indices.push_back(i + 3);
		}
	}

};
#endif
