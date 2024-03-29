#include "World.h"

World::World(){
	srand(time(NULL));
	width = 100;
	height =100;
	depth = 100;
	// storage matrix
	cubs = std::vector<uint8_t>(width*height*depth, 0);
	index = std::vector<int>(width*height*depth * 6, -1);
	// do corners
	doPoint(0, 0, depth/4+(rand()%depth/2));
	doPoint(width - 1,0, depth / 4 + (rand() % depth / 2));
	doPoint(0, height - 1, depth / 4 + (rand() % depth / 2));
	doPoint(width - 1, height - 1, depth / 4 + (rand() % depth / 2));
	// do Borders
	doLine(0, 0, width - 1, 0);
	doLine(0, 0, 0, width - 1);
	doLine(width - 1, 0, width - 1, height - 1);
	doLine(0, height - 1, width - 1, height - 1);
	// do world
	doSquare(0, 0, width - 1, height - 1);
	// set trees
	for (int i = 0; i < width; ++i) {
		int randx = rand()%width;
		int randy = rand() % height;
		int size = getSize(randx, randy);
		// trunk
		for (int z = size; z < size + 5 && z<depth; ++z) {
			cubs[coord(randx, randy, z)] = 2;
		}
		// leaves
		if (inside(randx, randy, size + 6)) cubs[coord(randx, randy, size + 6)] = 6;
		if (inside(randx + 1, randy, size + 5)) cubs[coord(randx + 1, randy, size + 5)] = 6;
		if (inside(randx - 1, randy, size + 5)) cubs[coord(randx - 1, randy, size + 5)] = 6;
		if (inside(randx, randy + 1, size + 5)) cubs[coord(randx, randy + 1, size + 5)] = 6;
		if (inside(randx, randy - 1, size + 5)) cubs[coord(randx, randy - 1, size + 5)] = 6;
	}
}

/*
	Destructor
*/
World::~World(){
	cubs.clear();
	index.clear();
}
/*
	Fills with cubes x,y position to size height
*/
void World::doPoint(int x, int y, int size) {
	for (int z = 0; z < size; ++z) {
		if (z < size / 2) cubs[coord(x, y, z)] = 3;
		else cubs[coord(x, y, z)] = 1;
	}
}

/*
	Fills a line from x0,y0 to x1,y1 with cubes with random height depending on the initial positions height
*/
void World::doLine(int x0, int y0, int x1, int y1) {
	int init = getSize(x0, y0);
	int end = getSize(x1, y1);
	// horitzontal
	if (x0 == x1) {
		int x = x0;
		for (int y = y0+1; y < y1; ++y) {
			int rando = rand() % 100;
			int togo = y1 - y;
			if (togo <= abs(end - init)) init += (end - init) / togo;
			else if (rando<10) init -= 1; // go down
			else if (rando>90) init += 1; // go up
			if (init>depth - 10) init = depth - 10;// too high
			doPoint(x, y, init);
		}
	}
	// vertical
	else if (y0 == y1) {
		int y = y0;
		for (int x = x0+1; x < x1; ++x) {
			int rando = rand() % 100;
			int togo = x1 - x;
			if (togo <= abs(end - init)) init += (end - init) / togo;
			else if (rando<10) init -= 1;// go down
			else if (rando>90) init += 1;// go up
			if (init>depth - 10) init = depth - 10; // too high
			doPoint(x, y, init);
		}
	}
	else {
		std::cout << "ERROR!!" << std::endl;
	}
}
/*
	Fills a square of terran with cubes, dividing it by 2 doing 1 horitzontal and 1 vertical live and recursively calling the 4 resulting squares from the division
*/

void World::doSquare(int x0, int y0, int x1, int y1) {
	if (x1 - x0>1 && y1 - y0 > 1) {
		int randx = (rand() % (x1 - (x0+1))) + x0+1;
		int randy = (rand() % (y1 - (y0 + 1))) + y0 + 1;
		if (rand() % 2 == 0) {
			doLine(x0,randy,x1,randy);
			doLine(randx, y0, randx, randy);
			doLine(randx, randy, randx, y1);
		}
		else {
			doLine(randx, y0, randx, y1);
			doLine(x0, randy, randx, randy);
			doLine(randx, randy, x1, randy);
		}
		doSquare(x0, y0, randx, randy);
		doSquare(randx, y0, x1, randy);
		doSquare(x0, randy, randx, y1);
		doSquare(randx, randy, x1, y1);
	}
}
/*
	retruns how many cubes does a x,y position have
*/
int World::getSize(int x, int y) {
	int z = 0;
	while (z < depth && cubs[coord(x,y,z)]!=0) {
		++z;
	}
	return z;
}

//return an algoritm for run 3d matrix
inline unsigned World::coord(unsigned x, unsigned y, unsigned z){ return depth*(x*height + y) + z; }

//comprovate if is inside of the cube in de x, y,z position
inline bool World::inside(int x, int y, int z){ return (0 <= x && x < width) && (0 <= y && y < height) && (0 <= z && z < depth); }

//comprovate if cube in position exists
bool World::isEmpty(unsigned x, unsigned y, unsigned z){ return cubs[coord(x, y, z)] == 0; }

//generate vbo array of vertex
void World::generator(std::vector<Vertex> &vbo){
	int numvertex = 0;
	int xp, yp, zp;
	glm::vec3 director;
	// skybox
	calcVertex(-10, -10, -10, vbo, glm::vec3(0, height+20, depth+20), -1);
	calcVertex(-10, -10, -10, vbo, glm::vec3(width+20, 0, depth + 20), -1);
	calcVertex(-10, -10, -10, vbo, glm::vec3(width + 20, height + 20,0), -1);
	calcVertex(10 + width, 10 + height, 10 + depth, vbo, glm::vec3(0, -int(height) - 20, -int(depth) - 20), -1);
	calcVertex(10 + width, 10 + height, 10 + depth, vbo, glm::vec3(-int(width) - 20, 0, -int(depth) - 20), -1);
	calcVertex(10 + width, 10 + height, 10 + depth, vbo, glm::vec3(-int(width) - 20, -int(height) - 20, 0), -1);
	//xPosition = i/(depth*height)
	//yPosition = (i / depth)%height
	//zPosition = i%depth
	for (int i = 0; i < width*height*depth; i++){
		if (cubs[i]){
			//comprovate if neightboards exists
			//fist comprovate is the cube is the border cube
			//calc x, y and z position of the cub
			xp = i / (depth*height);
			yp = (i / depth) % height;
			zp = i%depth;
			//comprovate if neightboards are inside of the world and if don't exists, call createVertex()
			if (!inside(xp - 1, yp, zp) || isEmpty(xp - 1, yp, zp)){
				//left face
				calcVertex(xp, yp, zp, vbo, glm::vec3(0, 1, 1), cubs[i]);
			}if (!inside(xp + 1, yp, zp) || isEmpty(xp + 1, yp, zp)){
				//right face
				calcVertex(xp+1, yp+1, zp+1, vbo, glm::vec3(0, -1, -1), cubs[i]);

			}if (!inside(xp , yp-1, zp) || isEmpty(xp , yp-1, zp)){
				//front face
				calcVertex(xp, yp, zp, vbo, glm::vec3(1, 0, 1), cubs[i]);

			}if (!inside(xp , yp+1, zp) || isEmpty(xp, yp+1, zp)){
				//back face
				calcVertex(xp + 1, yp + 1, zp + 1, vbo, glm::vec3(-1, 0, -1), cubs[i]);

			}if (!inside(xp, yp, zp-1) || isEmpty(xp, yp, zp-1)){
				//bot face
				calcVertex(xp, yp, zp, vbo, glm::vec3(1, 1, 0), cubs[i]);

			}if (!inside(xp, yp, zp+1) || isEmpty(xp, yp, zp+1)){
				//top face
				calcVertex(xp + 1, yp + 1, zp + 1, vbo, glm::vec3(-1, -1, 0), cubs[i]);
			}
			
		}
	}
}
/* deprecated */
void World::deleteVertex(unsigned x, unsigned y, unsigned z, std::vector<Vertex> &vbo){

}
/* deprecated */
void World::insertVertex(unsigned x, unsigned y, unsigned z, std::vector<Vertex> &vbo){

}

//create de four vertex of the face
//parameters: x ,y ,z positions; vertex buffer object; vector distance 
// vertex have x,y,z,texID,r,g,b,a,u,v,nx,ny,nz
void World::calcVertex(int x, int y, int z, std::vector<Vertex> &vbo, glm::vec3 d, int id){
	Vertex v;
	x *= CUBESIZE;
	y *= CUBESIZE;
	z *= CUBESIZE;
	d *= CUBESIZE;
	float normal;
	if (d.x == d.z){
		if (d.x > 0) normal = -1;
		else normal = 1;
		//push first vertex
		v.setPosition(x, y, z);
		v.setId(id);
		v.setColor(255, 0, 0, 255);
		if (d.x < 0) v.setUV(1.0f, 1.0f);
		else v.setUV(0.0f, 0.0f);
		v.setNormal(0.0,normal, 0.0);
		vbo.push_back(v);

		//push second vertex
		v.setPosition(x, y, z+d.z);
		v.setId(id);
		v.setColor(255, 0, 0, 255);
		if (d.x < 0) v.setUV(1.0f, 0.0f);
		else v.setUV(0.0f, 1.0f);
		v.setNormal(0.0, normal, 0.0);
		vbo.push_back(v);

		//push third vertex
		v.setPosition(x+d.x, y, z + d.z);
		v.setId(id);
		v.setColor(255, 0, 0, 255);
		if (d.x < 0) v.setUV(0.0f, 0.0f);
		else v.setUV(1.0f, 1.0f);
		v.setNormal(0.0, normal, 0.0);
		vbo.push_back(v);

		//push fourth vertex 
		v.setPosition(x + d.x, y, z);
		v.setId(id);
		v.setColor(255, 0, 0, 255);
		if (d.x < 0) v.setUV(0.0f, 1.0f);
		else v.setUV(1.0f, 0.0f);
		v.setNormal(0.0, normal, 0.0);
		vbo.push_back(v);

	}else if (d.y == d.z){
		if (d.z > 0) normal = -1;
		else normal = 1;
		//push first vertex
		v.setPosition(x, y, z);
		v.setId(id);
		v.setColor(0, 255, 0, 255);
		if (d.z < 0) v.setUV(0.0f, 1.0f);
		else v.setUV(1.0f, 0.0f);
		v.setNormal(normal, 0.0, 0.0);
		vbo.push_back(v);

		//push second vertex
		v.setPosition(x, y+d.y, z);
		v.setId(id);
		v.setColor(0, 255, 0, 255);
		if (d.z < 0) v.setUV(1.0f, 1.0f);
		else v.setUV(0.0f, 0.0f);
		v.setNormal(normal, 0.0, 0.0);
		vbo.push_back(v);

		//push third vertex
		v.setPosition(x, y + d.y, z + d.z);
		v.setId(id);
		v.setColor(0, 255, 0, 255);
		if (d.z < 0) v.setUV(1.0f, 0.0f);
		else v.setUV(0.0f, 1.0f);
		v.setNormal(normal, 0.0, 0.0);
		vbo.push_back(v);

		//push fourth vertex 
		v.setPosition(x , y, z+d.z);
		v.setId(id);
		v.setColor(0, 255, 0, 255);
		if (d.z < 0) v.setUV(0.0f, 0.0f);
		else v.setUV(1.0f, 1.0f);
		v.setNormal(normal, 0.0, 0.0);
		vbo.push_back(v);
	}else{
		if (d.y > 0) normal = -1;
		else normal = 1;
		//push first vertex
		v.setPosition(x, y, z);
		v.setId(id);
		v.setColor(0, 0, 255, 255);
		v.setUV(0.0f, 1.0f);
		v.setNormal(0.0, 0.0, normal);
		vbo.push_back(v);

		//push second vertex
		v.setPosition(x+d.x, y, z);
		v.setId(id);
		v.setColor(0, 0, 255, 255);
		v.setUV(1.0f, 1.0f);
		v.setNormal(0.0, 0.0, normal);
		vbo.push_back(v);

		//push third vertex
		v.setPosition(x+d.x, y + d.y, z);
		v.setId(id);
		v.setColor(0, 0, 255, 255);
		v.setUV(1.0f, 0.0f);
		v.setNormal(0.0, 0.0, normal);
		vbo.push_back(v);

		//push fourth vertex 
		v.setPosition(x, y+d.y, z);
		v.setId(id);
		v.setColor(0, 0, 255, 255);
		v.setUV(0.0f, 0.0f);
		v.setNormal(0.0, 0.0, normal);
		vbo.push_back(v);
	}
}
/*
	Checks if a rectanlge fits into the world
*/
bool World::fits(glm::vec3 min, glm::vec3 max){
	min = min / CUBESIZE;
	max = max / CUBESIZE;
	for (int i = floor(min.x); i <= ceil(max.x);i++){
		for (int j = floor(min.y); j <= ceil(max.y); j++){
			for (int k = floor(min.z); k <= ceil(max.z); k++){
				if (inside(i, j, k) && cubs[coord(i, j, k)] != 0) return false;
			}
		}
	}
	return true;
}
/*
	checks if a position fits into the world
*/
bool World::fits2(glm::vec3 pos) {
	pos = pos / CUBESIZE;
	pos.x = floor(pos.x);
	pos.y = floor(pos.y);
	pos.z = floor(pos.z - 0.5);
	if (inside(pos.x, pos.y, pos.z) && cubs[coord(pos.x, pos.y, pos.z)] != 0) return false;
	if (inside(pos.x, pos.y, pos.z-1) && cubs[coord(pos.x, pos.y, pos.z-1)] != 0) return false;
	return true;
}
/*
checks if a position fits into the world
*/
bool World::fits3(glm::vec3 pos) {
	pos = pos / CUBESIZE;
	pos.x = floor(pos.x);
	pos.y = floor(pos.y);
	pos.z = floor(pos.z - 0.5);
	if (inside(pos.x, pos.y, pos.z) && cubs[coord(pos.x, pos.y, pos.z)] != 0) return false;
	if (inside(pos.x, pos.y, pos.z - 1) && cubs[coord(pos.x, pos.y, pos.z - 1)] != 0) return false;
	return true;
}
/*
	Try to remove the cubre resulting from a player in position looking in direction, returns true if suceed
*/
bool World::removeCube(glm::vec3 position, glm::vec3 direction) {
	//cubs[coord(v.x, v.y, v.z)] = 0;
	glm::vec3 cpos;
	int face;
	raycast(5, position, direction, cpos, face);
	// if the raycast suceeded remove the cube
	if (face != -1){
		cubs[coord(cpos.x, cpos.y, cpos.z)] = 0;
		return true;
	}
	return false;
}
/*
Try to place a cube resulting from a player in position looking in direction, returns true if suceed
*/
bool World::putCube(glm::vec3 position, glm::vec3 direction, int cubeTipe){
	//cubs[coord(v.x, v.y, v.z)] = 1;
	glm::vec3 cpos;
	int face;
	raycast(5, position, direction, cpos, face);
	// if the raycast succeded and the face of collision is empty place the new cube
	if (face != -1){
		cpos += axis[face];
		if (inside(cpos.x, cpos.y, cpos.z) && cubs[coord(cpos.x, cpos.y, cpos.z)] == 0) {
			cubs[coord(cpos.x, cpos.y, cpos.z)] = cubeTipe;
			return true;
		}
	}
	return false;
}
/*
	Gets the cubeID from a position
*/
int World::cubeTipe(glm::vec3 v){ 
	return cubs[coord(v.x, v.y, v.z)]; 
}
/*
	Converts a world coordinate into local matrix position
*/
glm::vec3 World::pointToGrid(glm::vec3 position){
	glm::vec3 v;
	v.x = floor(position.x/CUBESIZE);
	v.y = floor(position.y/CUBESIZE);
	v.z = floor(position.z/CUBESIZE);
	return v;
}
/*
	Emits a ray collinging with cubes until maxDist is reached, starting in position with the direction direction

	Returns:
		colisionPos point of the collision (x,y,z) 
		face 0-5 depending on the cube face that recieved the collision
*/
void World::raycast(float maxDist, glm::vec3 position, glm::vec3 direction, glm::vec3 &colisonPos, int &face){
	glm::vec3 currentPosition = position/ CUBESIZE;
	direction *= -1.0f;
	// white we didnt reach maxDist
	while (glm::length(currentPosition - position/CUBESIZE) < maxDist){
		std::cout << " operative. currentPositon = " <<  currentPosition.x << " , " << currentPosition.y << " , " << currentPosition.z << std::endl;
		glm::vec3 t = { 0, 0, 0 };
		//
		if (direction.x > 0) t.x = (ceil(currentPosition.x) - currentPosition.x );
		else t.x = (floor(currentPosition.x) - currentPosition.x);
		//
		if (direction.y > 0) t.y = (ceil(currentPosition.y) - currentPosition.y);
		else t.y = (floor(currentPosition.y) - currentPosition.y);
		//
		if (direction.z > 0) t.z = (ceil(currentPosition.z) - currentPosition.z) ;
		else t.z = (floor(currentPosition.z) - currentPosition.z);
		// check the closest collision non 0
		if (direction.x!=0) t.x = t.x / direction.x;
		if (direction.y != 0) t.y = t.y / direction.y;
		if (direction.z != 0) t.z = t.z / direction.z;
		if (t.x <= t.y && t.x <= t.z && t.x!=0){
			currentPosition = currentPosition + direction * t.x * 1.01f;
			if (direction.x < 0) face = 0;
			else face = 1;
		}
		else if (t.y <= t.z && t.y!=0){
			currentPosition = currentPosition + direction * t.y * 1.01f;
			if (direction.y < 0) face = 2;
			else face = 3;
		}
		else{
			currentPosition = currentPosition + direction * t.z * 1.01f;
			if (direction.z < 0) face = 4;
			else face = 5;
		}
		// if the collision is valid stop the loop
		if (inside(floor(currentPosition.x), floor(currentPosition.y), floor(currentPosition.z)) && cubs[coord(floor(currentPosition.x), floor(currentPosition.y), floor(currentPosition.z))] != 0) {
			colisonPos = { floor(currentPosition.x), floor(currentPosition.y), floor(currentPosition.z) };
			return;
		}
	}
	face = -1;
}