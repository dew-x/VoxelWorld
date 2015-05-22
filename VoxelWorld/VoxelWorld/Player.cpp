#include "Player.h"

float sgn(float a){
	if (a < 0)return -1;
	else return 1;
}

Player::Player(glm::vec3 pos)
{
	position = pos;
}


Player::~Player()
{
}

glm::vec3 Player::getCameraFront(){
	//std::cout << "direction : " << direction.x << " " << direction.y << " " << direction.z << "\n";
	return direction + position;
}
glm::vec3 Player::getDirection(){
	return glm::normalize(direction);
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
	float cspeed = 20;
	//angleH = sp * x;
	//angleV = sp * y;
	glm::vec3 xAxis = { 0, 0, -1 };
	glm::vec3 yAxis = { 0, -1, 0 };
	direction = glm::normalize(glm::rotate(direction,x/cspeed, xAxis));
	glm::vec3 newDirection = glm::normalize(glm::rotate(direction, (y / cspeed)*sgn(direction.x), yAxis));
	/*if (newDirection.x <= 0 && newDirection.y <= 0) { 
		newDirection.x = direction.x;
		newDirection.y = direction.y;
	}*/
	direction = glm::normalize(newDirection);

}
void Player::moveDeltas(float x, float y){
	glm::vec3 dir = { direction.x, direction.y, 0 };
	dir = glm::normalize(dir);
	dir *= x;
	glm::vec3 dirP = { -direction.y, direction.x , 0};
	dirP = glm::normalize(dirP);
	dirP *= y;
	dir += dirP;
	dir = glm::normalize(dir);
	position += (dir*0.1f);
}
void Player::doJump(){

}

void Player::setDirection(glm::vec3 d){
	direction = glm::normalize(d);
}

