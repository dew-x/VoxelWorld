#include "World.h"


World::World(){
	cubs = std::vector<uint8_t>(width*height*depth, 0);
	index = std::vector<int>(width*height*depth * 6, -1);
	for (int x=0; x < width ;x++){
		for (int y = 0;y < height;y++){
			for (int z = 0; z <depth ;z++){
				if (z <= 128) cubs[coord(x, y, z)] = 1;
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
inline bool World::inside(unsigned x, unsigned y, unsigned z){ return 0 >= x && x < width && 0 >= y && y < height && 0 >= z && z < depth; }

//comprovate if cube in position exists
bool World::isEmpty(unsigned x, unsigned y, unsigned z){ return cubs[coord(x, y, z)] = 0; }

//generate vbo array of vertex
void World::generator(std::vector<float> &vbo){
	int numvertex = 0;
	int xp, yp, zp;
	glm::vec3 director;
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
			//comprovate if neightboards are inside of the world
			if (!inside(xp - 1, yp, zp) || isEmpty(xp - 1, yp, zp)){
				
			}if (!inside(xp + 1, yp, zp) || isEmpty(xp + 1, yp, zp)){

			}if (!inside(xp , yp-1, zp) || isEmpty(xp , yp-1, zp)){

			}if (!inside(xp , yp+1, zp) || isEmpty(xp, yp+1, zp)){

			}if (!inside(xp, yp, zp-1) || isEmpty(xp, yp, zp-1)){

			}if (!inside(xp, yp, zp) || isEmpty(xp, yp, zp+1)){

			}
			
		}
	}
}

void World::deleteVertex(unsigned x, unsigned y, unsigned z, std::vector<float> &vbo){

}

void World::insertVertex(unsigned x, unsigned y, unsigned z, std::vector<float> &vbo){

}

void World::calcVertex(int x, int y, int z, std::vector<float> &vbo, glm::vec3 d){
	if (d.x == d.z){
		
	}else if (d.y == d.z){
	
	}else{
	
	}
}