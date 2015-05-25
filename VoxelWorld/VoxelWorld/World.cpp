#include "World.h"


World::World(){
	
	width = 256;
	height =256;
	depth = 256;
	cubs = std::vector<uint8_t>(width*height*depth, 0);
	index = std::vector<int>(width*height*depth * 6, -1);
	int n = 50;
	for (int x=0; x < width ;x++){
		for (int y = 0;y < height;y++){
			for (int z = 0; z <depth ;z++){
				if (z < depth/2){
					if (!(x <= z && y <= z)) cubs[coord(x, y, z)] = (rand() % 3)+1;
					else cubs[coord(x, y, z)] = 0;
				}
				else cubs[coord(x, y, z)] = 0;
			}
		}
	}
}


World::~World(){
	cubs.clear();
	index.clear();
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

void World::deleteVertex(unsigned x, unsigned y, unsigned z, std::vector<Vertex> &vbo){

}

void World::insertVertex(unsigned x, unsigned y, unsigned z, std::vector<Vertex> &vbo){

}

//create de four vertex of the face
//parameters: x ,y ,z positions; vertex buffer object; vector distance 
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
		v.setUV(0.0f, 0.0f);
		v.setNormal(0.0,normal, 0.0);
		vbo.push_back(v);

		//push second vertex
		v.setPosition(x, y, z+d.z);
		v.setId(id);
		v.setColor(255, 0, 0, 255);
		v.setUV(0.0f, 1.0f);
		v.setNormal(0.0, normal, 0.0);
		vbo.push_back(v);

		//push third vertex
		v.setPosition(x+d.x, y, z + d.z);
		v.setId(id);
		v.setColor(255, 0, 0, 255);
		v.setUV(1.0f, 1.0f);
		v.setNormal(0.0, normal, 0.0);
		vbo.push_back(v);

		//push fourth vertex 
		v.setPosition(x + d.x, y, z);
		v.setId(id);
		v.setColor(255, 0, 0, 255);
		v.setUV(1.0f, 0.0f);
		v.setNormal(0.0, normal, 0.0);
		vbo.push_back(v);
	}else if (d.y == d.z){
		if (d.z > 0) normal = -1;
		else normal = 1;
		//push first vertex
		v.setPosition(x, y, z);
		v.setId(id);
		v.setColor(0, 255, 0, 255);
		v.setUV(1.0f, 0.0f);
		v.setNormal(normal, 0.0, 0.0);
		vbo.push_back(v);

		//push second vertex
		v.setPosition(x, y+d.y, z);
		v.setId(id);
		v.setColor(0, 255, 0, 255);
		v.setUV(0.0f, 0.0f);
		v.setNormal(normal, 0.0, 0.0);
		vbo.push_back(v);

		//push third vertex
		v.setPosition(x, y + d.y, z + d.z);
		v.setId(id);
		v.setColor(0, 255, 0, 255);
		v.setUV(0.0f, 1.0f);
		v.setNormal(normal, 0.0, 0.0);
		vbo.push_back(v);

		//push fourth vertex 
		v.setPosition(x , y, z+d.z);
		v.setId(id);
		v.setColor(0, 255, 0, 255);
		v.setUV(1.0f, 1.0f);
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

void World::eliminateCube(glm::vec3 v) {
	cubs[coord(v.x, v.y, v.z)] = 0;
}

void World::putCube(glm::vec3 v){
	cubs[coord(v.x, v.y, v.z)] = 1;
}

int World::cubeTipe(glm::vec3 v){ 
	return cubs[coord(v.x, v.y, v.z)]; 
}

glm::vec3 World::transformLookAt(glm::vec3 lookAt){
	glm::vec3 v;
	v.x = floor(lookAt.x/CUBESIZE);
	v.y = floor(lookAt.y/CUBESIZE);
	v.z = floor(lookAt.z/CUBESIZE);
	return v;
}