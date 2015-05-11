#include "Player.h"


Player::Player(glm::vec3 pos)
{
	position = pos;
}


Player::~Player()
{
}

glm::vec3 Player::getCameraFront(){
	return{ 0, 0, 0 };
}
glm::vec3 Player::getCameraUp(){
	return{ 0, 0, 0 };
}
glm::vec3 Player::getPosition(){
	return position;
}
glm::vec3 Player::getMin(){
	return{ 0, 0, 0 };
}
glm::vec3 Player::getMax(){
	return{ 0, 0, 0 };
}
void Player::addMouseDeltas(float x, float y){
}
void Player::moveDeltas(float x, float y){
}
void Player::doJump(){
}