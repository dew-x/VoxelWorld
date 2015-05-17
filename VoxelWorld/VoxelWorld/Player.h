#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>
class Player
{
private:
	glm::vec3 position;
	glm::vec3 min, max;
	glm::vec3 direction;
	float angleH;
	float angleV;
public:
	Player(glm::vec3 pos);
	~Player();
	glm::vec3 getCameraFront();
	glm::vec3 getCameraUp();
	glm::vec3 getPosition();
	glm::vec3 getMin();
	glm::vec3 getMax();
	void addMouseDeltas(float x, float y);
	void moveDeltas(float x, float y);
	void doJump();
	void setDirection(glm::vec3 d);
};

