#pragma once
#include <iostream>
#include <math.h>
#include <set>
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>

class World{
	uint8_t width;
	uint8_t height;
	uint8_t depth;
	std::vector<uint8_t> cubs;
	std::vector<int> index;
public:
	World();
	~World();
	inline unsigned coord(unsigned x, unsigned y, unsigned z);
	inline bool inside(unsigned x, unsigned y,unsigned z);
	void generator(std::vector<float> &vbo);
	void deleteVertex(unsigned x, unsigned y, unsigned z, std::vector<float> &vbo);
	void insertVertex(unsigned x, unsigned y, unsigned z, std::vector<float> &vbo);
	bool isEmpty(unsigned x, unsigned y, unsigned z);
	void World::calcVertex(int x, int y, int z, std::vector<float> &vbo, glm::vec3 d);
};

