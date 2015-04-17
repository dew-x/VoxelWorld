#include "Geometry.h"
#include "ErrorManagement.h"
#include <iostream>
#include <fstream>

using namespace std;


/*
* Constructor 
*/
Geometry::Geometry(){
	loadBasic3DObjects();
	_currentPlayerObject = PLAYER_OBJECT;

}


Geometry::~Geometry(){
	for (int i = 0; i < NUMBASICOBJECTS; i++) {
		if (_verticesData[i] != 0){
			delete _verticesData[i];
		}
	}	
}

/*
* Get the current player object
*/
int Geometry::getCurrentPlayerObject() {
	return _currentPlayerObject;
}

/*
* Define the geometry of the basic 3D objects
*/
void Geometry::loadBasic3DObjects() {
	int numVertices = 0;
	//Define the number of vertices for all the basic game objects
	_numVertices[PYRAMID_TYPE] = 18;
	_numVertices[CUBE_TYPE] = 36;
	_numVertices[PLANE_TYPE] = 6;

	//We are going to create two basic cubes: blue and white
	Vertex v;
	for (int i = 0; i < NUMBASICOBJECTS; i++) {
		numVertices = _numVertices[i];
		_verticesData[i] = new Vertex[numVertices];
		if (_verticesData[i] == 0)
			ErrorManagement::errorRunTime("System was not able to allocate the basic game object");

		//By default all the objects are white, the color will be defined from the scene file
		v.setColor(255, 255, 255, 255);
		//set the same color for all the vertices
		for (int j = 0; j < numVertices; j++) {
			_verticesData[i][j].color = v.color;
		}
		//define the vertices based on the object typology
		switch (i) {
		case PYRAMID_TYPE:
			createPyramid(i);
			break;
		case CUBE_TYPE:
			createCube(i);
			break;
		case PLANE_TYPE:
			createPlane(i);
			break;
		}

	}
}

/*
* Create a unitary cube composed by 18 triangles. The center of the cube is at (0,0,0)
* @param i is the position of the data structure that contains the object definitions
*/
void Geometry::createCube(int i) {

	/*
		P3*******P4
	   *		*
	  *		   *
	  P1******P2

	    P7*******P8
	   *		*
	  *		   *
	  P5******P6

	 */

	//....
}


/*
* Create a unitary pyramid composed by 6 triangles. The base's pyramid is on the plane z=0
* @param i is the position of the data structure that contains the object definitions
*/
void Geometry::createPyramid(int i) {
	
	/*
	P3*****P4
	* *	  **
	*  P0  *
	* *  * *
	P1*****P2

	*/

	// top: P1, P4, P2, P4, P1, P3
	_verticesData[i][0].setPosition(-0.5f, -0.5f, -0.5f);
	_verticesData[i][0].setUV(0, 0);
	_verticesData[i][1].setPosition(0.5f, 0.5f, -0.5f);
	_verticesData[i][1].setUV(1, 1);
	_verticesData[i][2].setPosition(0.5f, -0.5f, -0.5f);
	_verticesData[i][2].setUV(1, 0);
	_verticesData[i][3].setPosition(0.5f, 0.5f, -0.5f);
	_verticesData[i][3].setUV(1, 1);
	_verticesData[i][4].setPosition(-0.5f, -0.5f, -0.5f);
	_verticesData[i][4].setUV(0, 0);
	_verticesData[i][5].setPosition(-0.5f, 0.5f, -0.5f);
	_verticesData[i][5].setUV(0, 1);

	//bottom lateral side P0,P4, P3
	_verticesData[i][6].setPosition(0.0f,0.0f, 0.5f);
	_verticesData[i][6].setUV(0.5f, 1.0f);
	_verticesData[i][7].setPosition(0.5f, 0.5f, -0.5f);
	_verticesData[i][7].setUV(0.0f, 0.0f);
	_verticesData[i][8].setPosition(-0.5f, 0.5f, -0.5f);
	_verticesData[i][8].setUV(1.0f, 0.0f);

	//left lateral side P0, P3, P1
	_verticesData[i][9].setPosition(0.0f, 0.0f, 0.5f);
	_verticesData[i][9].setUV(0.5f, 1.0f);
	_verticesData[i][10].setPosition(-0.5f, 0.5f, -0.5f);
	_verticesData[i][10].setUV(0.0f, 0.0f);
	_verticesData[i][11].setPosition(-0.5f, -0.5f, -0.5f);
	_verticesData[i][11].setUV(1.0f, 0.0f);


	//top lateral side P0, P1, P2
	_verticesData[i][12].setPosition(0.0f, 0.0f, 0.5f);
	_verticesData[i][12].setUV(0.5f, 1.0f);
	_verticesData[i][13].setPosition(-0.5f, -0.5f, -0.5f);
	_verticesData[i][13].setUV(0.0f, 0.0f);
	_verticesData[i][14].setPosition(0.5f, -0.5f, -0.5f);
	_verticesData[i][14].setUV(1.0f, 0.0f);

	//right lateral side, P0, P2, P4
	_verticesData[i][15].setPosition(0.0f, 0.0f, 0.5f);
	_verticesData[i][15].setUV(0.5f, 1.0f);
	_verticesData[i][16].setPosition(0.5f, -0.5f, -0.5f);
	_verticesData[i][16].setUV(0.0f, 0.0f);
	_verticesData[i][17].setPosition(0.5f, 0.5f, -0.5f);
	_verticesData[i][17].setUV(1.0f, 0.0f);
}


/*
* Create a unitary square composed by 6 triangles. The center of the cube is at (0,0,0)
* @param i is the position of the data structure that contains the object definitions
*/
void Geometry::createPlane(int i) {

	/*
	  P3*****P4
	  *		**
	  *	  *	 *
	  *	*	 *
	  P1*****P2

	*/

	// top: P1, P2, P4, P4, P3, P1
	_verticesData[i][0].setPosition(-0.5f, -0.5f, 0.0f);
	_verticesData[i][0].setUV(0, 0);
	_verticesData[i][1].setPosition(0.5f, -0.5f, 0.0f);
	_verticesData[i][1].setUV(1, 0);
	_verticesData[i][2].setPosition(0.5f, 0.5f, 0.0f);
	_verticesData[i][2].setUV(1, 1);
	_verticesData[i][3].setPosition(0.5f, 0.5f, 0.0f);
	_verticesData[i][3].setUV(1, 1);
	_verticesData[i][4].setPosition(-0.5f, 0.5f, 0.0f);
	_verticesData[i][4].setUV(0, 1);
	_verticesData[i][5].setPosition(-0.5f, -0.5f, 0.0f);
	_verticesData[i][5].setUV(0, 0);
}

/*
* Load the game elements from a text file
*/
void Geometry::loadGameElements(char fileName[100]){		
	GameObject tempObject;

	/*
	* Replace the following code that defines one game object by the code responsible of reading your game file specification and store each one of the game objects
	*/

	tempObject._color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	tempObject._objectType = PYRAMID_TYPE;
	tempObject._angle = 0;
	tempObject._rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	tempObject._scale = glm::vec3(1.0f, 1.0f, 1.0f);
	tempObject._translate = glm::vec3(0.0f, 0.0f, 0.0f);
	tempObject._angleXYPlane = 0;
	tempObject._angleXZPlane = 0;
	tempObject._textureFile = "./resources/textures/floor.jpg";
	tempObject._textureRepetion = false;

	_listOfObjects.resize(1);
	_listOfObjects[0] = tempObject;
	
	/* Text format
	<number of game elements>
	.....
	*/
	
	/*
	int numGameElements;
	std::string tempStr;
	GameObject tempGameObject;
	ifstream file;
	file.open(fileName);

	if (file.is_open()){		
		file >> numGameElements;
		_listOfObjects.resize(numGameElements);
		for (int i = 0; i < numGameElements; i++) {
			//Read the game file and write the data in the tempGameObject variable

			

			_listOfObjects[i] = tempGameObject;
		}
		file.close();
	}
	else{
		string message = "The file " + string(fileName) + " doesn't exists";
		ErrorManagement::errorRunTime(message);
	}
	*/

}

/*
* Get the vertices data for an specific object
* @param objectID is the identifier of the requested object
* @return Vertex * is an array with all the vertices data
*/
Vertex * Geometry::getData(int objectID){
	return _verticesData[objectID];
}

/*
* Get the number of vertices for an specific object
* @param objectID is the identifier of the requested object
* @return int is the number of vertices
*/

int Geometry::getNumVertices(int objectID){
	return _numVertices[objectID];
}

/*
* Get the number of elements to render
*/
int Geometry::getNumGameElements() {
	return _listOfObjects.size();
}

/*
* Get the number of vertices of an specific game element
* @param objectID is the identifier of the requested object
*/
GameObject & Geometry::getGameElement(int objectID) {
	return (_listOfObjects[objectID]);
}
