#include "World.h"


World::World(){
	cubs[width*height*depth];
}


World::~World(){

}

inline unsigned World::coord(unsigned x, unsigned y, unsigned z){ return depth*(x*height + y) + z; }

inline bool World::inside(unsigned x, unsigned y, unsigned z){

}

void World::generator(std::vector<float>* vbo){

}

void World::deleteVertex(unsigned x, unsigned y, unsigned z, std::vector<float>* vbo){

}

void World::insertVertex(unsigned x, unsigned y, unsigned z, std::vector<float>* vbo){

}

bool World::isEmpty(unsigned x, unsigned y, unsigned z){

}