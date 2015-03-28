#pragma once

#include <iostream>
#include <math.h>
#include <set>
#include <cstdint>

/*
CLass to handle the data of a small piece of the map, have linkts to its neigboors

2D bidirectional list
*/

class Chunk {
private:
	uint8_t *matrix; //pointer matrix 
	int x; // x position
	int y; // y position
	int z;
	Chunk *left; // neighbord pointer left
	Chunk *right; // neighbord pointer right
	Chunk *top; // neighbord pointer top
	Chunk *bot; // neighbord pointer bot
	bool isCalled; // boolean is called
	std::set<unsigned> *exists; // pointer set exist chunk
public:
	Chunk(int, int, std::set<unsigned>*); //constructor
	Chunk(int, int, std::set<unsigned>*, Chunk* r, Chunk* b, Chunk* l, Chunk* t); // constructor 2
	~Chunk(); //destructor
	void randomChunk(); //randomsize all values of chunk matrix
	void setChunk(int id, Chunk *chunk); //asign neighbords of chunk 
	Chunk* getChunk(int id); //return neighbords
	bool areDiferentChunk(int x, int y); // 
	//void spawnNeighbors(SDL_Rect window, ItemMap*); // create neighbords if i need
	void resetCalls(); // return booleans isCalled as false
	int getMapValue(int x, int y); // gets the tile value of the positions x,y relative to current chunk
private:
};

