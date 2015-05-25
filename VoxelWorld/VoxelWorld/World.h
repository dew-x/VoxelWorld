#pragma once
#include <iostream>
#include <math.h>
#include <set>
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include "Vertex.h"
#include <stdlib.h> 

#define CUBESIZE 2.0f
class World{
	std::vector<uint8_t> cubs;
	std::vector<int> index;
public:
	unsigned width;
	unsigned height;
	unsigned depth;
	World();
	~World();
	inline unsigned coord(unsigned x, unsigned y, unsigned z);
	inline bool inside(int x, int y,int z);
	void generator(std::vector<Vertex> &vbo);
	bool fits(glm::vec3 min, glm::vec3 max);
	void deleteVertex(unsigned x, unsigned y, unsigned z, std::vector<Vertex> &vbo);
	void insertVertex(unsigned x, unsigned y, unsigned z, std::vector<Vertex> &vbo);
	bool isEmpty(unsigned x, unsigned y, unsigned z);
	void World::calcVertex(int x, int y, int z, std::vector<Vertex> &vbo, glm::vec3 d, int id);
	void removeCube(glm::vec3 position, glm::vec3 direction);
	void putCube(glm::vec3 position, glm::vec3 direction);
	int cubeTipe(glm::vec3 v);
	glm::vec3 pointToGrid(glm::vec3 position);
	int raycast(float maxDist);
};

