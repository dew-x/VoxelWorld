#include "Player.h"

/*
	Returns the sign of the number a -1 if negative 1 if positive
*/
float sgn(float a){
	if (a < 0)return -1;
	else return 1;
}

Player::Player(glm::vec3 pos)
{
	position = pos; // player current position
	cubeTypeInHand = 1; // id of the cube that player places in the world
	acceleration = { 0, 0, -0.3 }; // player acceleration fall down untill collision
}


Player::~Player()
{
}

/*
	Returns a point in front of the player in the direction where hs is looking
*/

glm::vec3 Player::getCameraFront(){
	return direction + position;
}
/*
	Returns the player direction (normalized)	
*/
glm::vec3 Player::getDirection(){
	return glm::normalize(direction);
}
/*
	Camera up vector
*/
glm::vec3 Player::getCameraUp(){
	return{ 0, 0, 0 };
}
/*
	Returns player position
*/
glm::vec3 Player::getPosition(){
	return position;
}
/*
	Returns player collision rectangle minimum position
*/
glm::vec3 Player::getMin(){
	return{ position.x+0.4, position.y+0.4, position.z-2.4};
}
/*
Returns player collision rectangle maximum position
*/
glm::vec3 Player::getMax(){
	return{ position.x+0.6, position.y+0.6, position.z+0.6 };
}
/*
	Move the player looking direction with mouse deltas
*/
void Player::addMouseDeltas(float x, float y){
	float cspeed = 20; // camera speed
	//angleH = sp * x;
	//angleV = sp * y;
	glm::vec3 xAxis = { 0, 0, -1 };
	glm::vec3 yAxis = { 0, -1, 0 };
	direction = glm::normalize(glm::rotate(direction,x/cspeed, xAxis)); // rotate direction on xAxis
	glm::vec3 newDirection = glm::normalize(glm::rotate(direction, (y / cspeed)*sgn(direction.x), yAxis)); // rotate direction on yAxis
	/*if (newDirection.x <= 0 && newDirection.y <= 0) { 
		newDirection.x = direction.x;
		newDirection.y = direction.y;
	}*/
	direction = glm::normalize(newDirection);

}
/*
	Update position based on keys pressed
*/
void Player::moveDeltas(float x, float y, World *w){
	// we move in a 3d world but we can only move on 2 directions x and y z is controlled by gravity
	// x equals to direction vector
	glm::vec3 dir = { direction.x, direction.y, 0 };
	dir = glm::normalize(dir);
	dir *= x;
	// y equals to the perpendicular of direction vector
	glm::vec3 dirP = { -direction.y, direction.x , 0};
	dirP = glm::normalize(dirP);
	dirP *= y;
	dir += dirP;
	dir = glm::normalize(dir);
	glm::vec3 oldPosition = position;
	position += (dir*0.1f);
	glm::vec3 ofsetWorld = { w->width*CUBESIZE, w->height*CUBESIZE, w->depth*CUBESIZE };
	// if the new position collides go to old Position
	if (!w->fits2(position)) position = oldPosition;
}
/*
	Sets the player direction
*/
void Player::setDirection(glm::vec3 d){
	direction = glm::normalize(d);
}
/*
updates player position according to gravity
*/
void Player::addGravity(World *w){
	// 
	std::cout << " acceleration is " << acceleration.x << " " << acceleration.y << " " << acceleration.z << std::endl;
 	glm::vec3 oldPosition = position;
	position.z += acceleration.z;
	if (acceleration.z > GRAVITY) acceleration.z -= 0.01f;
	else acceleration.z = GRAVITY;
	// if the new position collides go to old Position
	if (!w->fits3(position)) position = oldPosition;
}
/*
	inverts acceleration
*/
void Player::changeAcceleration(){ if (acceleration.z == GRAVITY) acceleration.z = -GRAVITY; }
/*
	returns the cube that the player will place
*/
int Player::getCubeType(){ return cubeTypeInHand; }
/*
	sets the cube that the player will place
*/
void Player::changeCubeType(int type){ cubeTypeInHand = type;}

