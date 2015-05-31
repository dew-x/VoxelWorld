#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include "World.h"

/*
	Player class

	Handles player information
	-Position
	-Acceleration
	-Direction
	-Inventory

	Have functions to interact with the view and the world

*/

#define GRAVITY -0.25f

class Player
{
private:
	glm::vec3 direction;
	glm::vec3 position;
	glm::vec3 min, max;
	int cubeTypeInHand;
	glm::vec3 acceleration;
public:
	Player(glm::vec3 pos);
	~Player();
	glm::vec3 getCameraFront();
	glm::vec3 getDirection();
	glm::vec3 getCameraUp();
	glm::vec3 getPosition();
	glm::vec3 getMin();
	glm::vec3 getMax();
	void addMouseDeltas(float x, float y);
	void moveDeltas(float x, float y, World *w);
	void addGravity(World *w);
	void setDirection(glm::vec3 d);
	void destroyCube();
	void changeAcceleration();
	void changeCubeType(int type);
	int getCubeType();
};

