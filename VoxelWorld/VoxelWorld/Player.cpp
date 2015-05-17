#include "Player.h"


Player::Player(glm::vec3 pos)
{
	position = pos;
}


Player::~Player()
{
}

glm::vec3 Player::getCameraFront(){
	std::cout << "direction : " << direction.x << " " << direction.y << " " << direction.z << "\n";
	return direction;

}

glm::vec3 Player::getCameraUp(){
	return{ 0, 0, 0 };
}

glm::vec3 Player::getPosition(){
	std::cout << "position : " << position.x << " " << position.y << " " << position.z << "\n";
	//system("pause");
	return position;
}

glm::vec3 Player::getMin(){
	return{ 0, 0, 0 };
}

glm::vec3 Player::getMax(){
	return{ 0, 0, 0 };
}

void Player::addMouseDeltas(float x, float y){
	//angleH = sp * x;
	//angleV = sp * y;
	glm::vec3 xAxis = { 1, 0, 0 };
	glm::vec3 yAxis = { 0, 1, 0 };
	direction = glm::rotate(direction, x, xAxis);
	direction = glm::rotate(direction, y, yAxis);
}


void Player::moveDeltas(float x, float y){
	position.x += x;
	position.z += y;
}


void Player::doJump(){
}

void Player::setDirection(glm::vec3 d){
	direction = d;
}