#include "Chunk.h"

/*chunk constructor
parameters: x position / y position / list set if exist this chunk
create a chunk, asign x and y position, create a matrix pointer with chunk_size and put boolean isCalled false. put this chunk in set exists*/

#define CHUNK_SIZE 16
#define CHUNK_SIZE_DEPTH 256
#define TILE_MAX 8
#define coord(x,y,z) CHUNK_SIZE_DEPTH*(x*CHUNK_SIZE+y)+z

Chunk::Chunk(int x, int y, std::set<unsigned>* exists){
	//save x and y cordinates
	this->x = x;
	this->y = y;
	z = CHUNK_SIZE_DEPTH;
	//create a matrix of int's of the chunk
	matrix = new uint8_t[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE_DEPTH];
	for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE_DEPTH; i++){
		matrix[i] = TILE_MAX;
	}
	//randomChunk();

	//initializate all pointers of NULL
	right = NULL;
	bot = NULL;
	left = NULL;
	top = NULL;

	isCalled = false;
}

/*chunk constructor 2
parameters: x position / y position / list set if exist this chunk / four pointers, right, bot, left, and top
create a chunk, asign x and y position, create a matrix pointer with chunk_size, asign pointer neighbords to foru pointers and put boolean isCalled false. put this chunk in set exists*/

Chunk::Chunk(int x, int y, std::set<unsigned>* exists, Chunk *r, Chunk* b, Chunk *l, Chunk *t){
	//save x, y cordinates
	this->x = x;
	this->y = y;
	z = CHUNK_SIZE_DEPTH;
	//create a matrix of int's of the chunk
	matrix = new uint8_t[CHUNK_SIZE * CHUNK_SIZE*CHUNK_SIZE_DEPTH];
	for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE_DEPTH; i++){
		matrix[i] = TILE_MAX;
	}
	//randomChunk();
	//initializate all pointers
	right = r;
	bot = b;
	left = l;
	top = t;

	isCalled = false;
}

/*chunk destructor
delete chunk 
*/
Chunk::~Chunk(){
	delete matrix;
}

/*randomChunk()
randomize all cells in the matrix chunk*/

void Chunk::randomChunk(){
	//matrix = new int[CHUNK_SIZE * CHUNK_SIZE];
	for (int i = 0; i < CHUNK_SIZE; i += 2) {
		for (int j = 0; j < CHUNK_SIZE; j += 2) {
			int p1, p2;
			if (j > 0) p1 = matrix[coord(i, (j - 2), 0)];
			else p1 = rand() % TILE_MAX;
			if (i > 0) p2 = matrix[coord((i - 2), j, 0)];
			else p2 = rand() % TILE_MAX;
			if (rand() % 10 == 0) matrix[coord(i, j, 0)] = rand() % TILE_MAX;
			else if (rand() % 2 == 0) matrix[coord(i, j, 0)] = p1;
			else matrix[coord(i, j , 0)] = p2;
			//log(1, "%d %d %d %d %d %d %d", i, j, p1, p2, matrix[coord(i, j)], coord((i - 2), j), coord(i, (j - 2)));
		}
	}
}

/*setChunk
parameters: int id chunk / pointer chunk
igualate neighbord pointers of this chunk*/

void Chunk::setChunk(int id, Chunk * chunk){
	if (id == 0) top = chunk;
	else if (id == 1) right = chunk;
	else if (id == 2) bot = chunk;
	else if (id == 3) left = chunk;
}

/*getChunk
parameters: int id chunk
return one neighbord of this chunk*/

Chunk* Chunk::getChunk(int id){
	if (id == 0) return top;
	else if (id == 1) return right;
	else if (id == 2) return bot;
	else if (id == 3) return left;
	return NULL;
}

/*areDiferentChunk
parameters; int x position, int y position
return true if this x and y cordinates are diferents of this chunk*/

bool Chunk::areDiferentChunk(int x, int y){
	if (this->x != x || this->y != y){
		return true;
	}
	else return false;
}

/*spawnNeighbords
parameters: window
create a neighbords if i need*/

/*void Chunk::spawnNeighbors(SDL_Rect window, ItemMap * itemap) {
	if (!isCalled) {
		isCalled = true;
		for (int i = 0; i < 4; i++){
			// is inside the screen window?
			if (rectInsideRect(window.x, window.y, window.w, window.h, (x + xval[i]) * CHUNK_SIZE - 2, (y + yval[i]) * CHUNK_SIZE - 2, CHUNK_SIZE + 4, CHUNK_SIZE + 4)) {
				Chunk * nei = getChunk(i);
				if (nei == NULL) {
					// does the chunk exists?
					if (exists->count(chunkUID(x + xval[i], y + yval[i])) != 0) {
						// search for it
						nei = search(x + xval[i], y + yval[i]);
					}
					else {
						// create id
						nei = new Chunk(x + xval[i], y + yval[i], exists);
						for (int j = 0; j < 10; j++){
							itemap->addRandomItem((double)nei->x, (double)nei->y, (double)CHUNK_SIZE, (double)CHUNK_SIZE);
						}
					}
					// add links
					setChunk(i, nei);
					nei->setChunk((i + 2) % 4, this);
				}
				//call spawnNeighbords whith neibord
				nei->spawnNeighbors(window, itemap);
			}
		}
	}
}*/

/*resetCalls
transform all booleans of chunk of false*/

void Chunk::resetCalls() {
	if (isCalled) {
		isCalled = false;
		for (int i = 0; i < 4; i++){
			Chunk * nei = getChunk(i);
			if (nei != NULL) nei->resetCalls();
		}
	}
}

/*int Chunk::getMapValue(int x, int y) {
	int ret = 7;
	if (x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_SIZE) {
		// the position is inside the chunk
		ret = matrix[coord(x, y)];
	}
	else if (x < 0) {
		if (left == NULL) left = search(this->x - 1, this->y);
		if (left != NULL) ret = left->getMapValue(CHUNK_SIZE + x, y);
	}
	else if (x >= CHUNK_SIZE) {
		if (right == NULL) right = search(this->x + 1, this->y);
		if (right != NULL) ret = right->getMapValue(x - CHUNK_SIZE, y);
	}
	else if (y < 0) {
		if (top == NULL) top = search(this->x, this->y - 1);
		if (top != NULL) ret = top->getMapValue(x, CHUNK_SIZE + y);
	}
	else if (y >= CHUNK_SIZE) {
		if (bot == NULL) bot = search(this->x, this->y + 1);
		if (bot != NULL)ret = bot->getMapValue(x, y - CHUNK_SIZE);
	}
	return ret;
}*/

//arreglar i fer amb un push 
void Chunk::generate(float* vertexs, unsigned* elements, std::vector<glm::vec3>* vertexArray, int* elementsArray){
	//calc the num of elements will need generated
	int element = 0;
	for (int i = 0; i < CHUNK_SIZE; i++){
		for (int j = 0; j < CHUNK_SIZE; j++){
			for (int k = 0; k < CHUNK_SIZE_DEPTH; k++){
				if (matrix[coord(i,j,k)] == 1) element++;
			}
		}
	}
	//create a new array of vertexs with new size
	vertexArray = new std::vector<glm::vec3>[element * 16];
	elementsArray = new int[6 * element];
	for (int i = 0; i < CHUNK_SIZE; i++){
		for (int j = 0; j < CHUNK_SIZE; j++){
			for (int k = 0; k < CHUNK_SIZE_DEPTH; k++){
				if (matrix[coord(i, j, k)] == 1){
					
				}
			}
		}
	}
}

