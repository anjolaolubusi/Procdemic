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
		/*for (float x = 0; x < xNum; x++) {
			for (float z = 0; z < zNum; z++) {
				srand((unsigned int)time(NULL));
				vMan.Add(glm::vec3(x / xNum, 0, z / zNum), glm::vec2(0, 0));
				vMan.Add(glm::vec3((x+1) / xNum, 0, z / zNum), glm::vec2(1, 0));
				vMan.Add(glm::vec3(x / xNum, 0, (z+1) / zNum), glm::vec2(0, 1));
				vMan.Add(glm::vec3((x+1) / xNum, 0, (z+1) / zNum), glm::vec2(1, 1));
			}
		}*/

        vMan.Add(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)); //0
        vMan.Add(glm::vec3(1.0f, 1.0f, -1.0), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        vMan.Add(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        vMan.Add(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)); //3

        vMan.Add(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)); //4
        vMan.Add(glm::vec3(-1.0f, 1.0f, 1.0), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        vMan.Add(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)),
        vMan.Add(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)); //7

        vMan.Add(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //8
        vMan.Add(glm::vec3(1.0f, 1.0f, 1.0), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        vMan.Add(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        vMan.Add(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //11

        vMan.Add(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //12
        vMan.Add(glm::vec3(1.0f, 1.0f, 1.0), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        vMan.Add(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        vMan.Add(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //15

        vMan.Add(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //16
        vMan.Add(glm::vec3(1.0f, 1.0f, -1.0), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        vMan.Add(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        vMan.Add(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //19

        vMan.Add(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)); //20
        vMan.Add(glm::vec3(1.0f, -1.0f, -1.0), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        vMan.Add(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        vMan.Add(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)); //23
	}
};

#endif
