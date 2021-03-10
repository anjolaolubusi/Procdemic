#ifndef PROCGEN_H
#define PROCGEN_H

#include <glm/glm.hpp>
#include <vector>
#include "VertexManager.h"	
#include <time.h>
#include <stdlib.h>

struct ProcGen{
	//Variable: heightMap, colourMap
	int xNum;
	int zNum;
	
	void AddTriangles(VertexManager& vMan){
		for (float x = 0; x < xNum; x++) {
			for (float z = 0; z < zNum; z++) {
				srand((unsigned int)time(NULL));
				vMan.Add(glm::vec3(x / xNum, 0, z / zNum), glm::vec2(0, 0));
				vMan.Add(glm::vec3((x+1) / xNum, 0, z / zNum), glm::vec2(1, 0));
				vMan.Add(glm::vec3(x / xNum, 0, (z+1) / zNum), glm::vec2(0, 1));
				vMan.Add(glm::vec3((x+1) / xNum, 0, (z+1) / zNum), glm::vec2(1, 1));
			}
		}
	}
};

#endif