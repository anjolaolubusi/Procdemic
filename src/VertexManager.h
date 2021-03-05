#ifndef VERTEXMANAGER_H
#define VERTEXMANAGER_H
#include <glm/glm.hpp>
#include <vector>
#include "Logger.h"

struct VertexManager {
	std::vector<glm::vec3> pos_list;
	std::vector<glm::vec2> tex_list;
	int total_num;

	void Add(glm::vec3 pos, glm::vec2 tex) {
		pos_list.push_back(pos);
		tex_list.push_back(tex);
		total_num = pos_list.size();
	}
};
#endif