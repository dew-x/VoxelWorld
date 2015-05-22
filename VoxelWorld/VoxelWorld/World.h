#pragma once
#include <iostream>
#include <math.h>
#include <set>
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include "Vertex.h"

#define CUBESIZE 2
class World{
	unsigned width;
	unsigned height;
	unsigned depth;
	std::vector<uint8_t> cubs;
	std::vector<int> index;
public:
	World();
	~World();
	inline unsigned coord(unsigned x, unsigned y, unsigned z);
	inline bool inside(unsigned x, unsigned y,unsigned z);
	void generator(std::vector<Vertex> &vbo);
	void deleteVertex(unsigned x, unsigned y, unsigned z, std::vector<Vertex> &vbo);
	void insertVertex(unsigned x, unsigned y, unsigned z, std::vector<Vertex> &vbo);
	bool isEmpty(unsigned x, unsigned y, unsigned z);
	void World::calcVertex(int x, int y, int z, std::vector<Vertex> &vbo, glm::vec3 d, int id);
};

