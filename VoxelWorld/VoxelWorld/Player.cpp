#include "Player.h"

float sgn(float a){
	if (a < 0)return -1;
	else return 1;
}

Player::Player(glm::vec3 pos)
{
	position = pos;
	cubeTypeInHand = 1;
	acceleration = { 0, 0, -0.3 };
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
	return{ position.x+0.4, position.y+0.4, position.z-2.4};
}
glm::vec3 Player::getMax(){
	return{ position.x+0.6, position.y+0.6, position.z+0.6 };
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
void Player::moveDeltas(float x, float y, World *w){
	glm::vec3 dir = { direction.x, direction.y, 0 };
	dir = glm::normalize(dir);
	dir *= x;
	glm::vec3 dirP = { -direction.y, direction.x , 0};
	dirP = glm::normalize(dirP);
	dirP *= y;
	dir += dirP;
	dir = glm::normalize(dir);
	glm::vec3 oldPosition = position;
	position += (dir*0.1f);
	glm::vec3 ofsetWorld = { w->width*CUBESIZE, w->height*CUBESIZE, w->depth*CUBESIZE };
	if (!w->fits2(position)) position = oldPosition;
	//if (!w->fits(ofsetWorld - getMax(), ofsetWorld - getMin())) position = oldPosition;
}

void Player::setDirection(glm::vec3 d){
	direction = glm::normalize(d);
}

void Player::addGravity(World *w){
	std::cout << " acceleration is " << acceleration.x << " " << acceleration.y << " " << acceleration.z << std::endl;
 	glm::vec3 oldPosition = position;
	position.z += acceleration.z;
	if (acceleration.z > GRAVITY) acceleration.z -= 0.01f;
	else acceleration.z = GRAVITY;
	if (!w->fits3(position)) position = oldPosition;
}

void Player::changeAcceleration(){ if (acceleration.z == GRAVITY) acceleration.z = -GRAVITY; }

int Player::getCubeType(){ return cubeTypeInHand; }

void Player::changeCubeType(int type){ cubeTypeInHand = type;}

