#pragma once
#include "Vertex.h"
#include <vector>
#include "GameObject.h"

#define PYRAMID_TYPE 0				
#define CUBE_TYPE 1
#define PLANE_TYPE 2
#define NUMBASICOBJECTS 3		//This counter doesn't include N_PLANE_TYPE because it is the same, it only changes how the texture coordinates are set

#define PLAYER_OBJECT 0			//The player object by default is the 0th game element

//This class stores and manipulates all the objects loaded from the text file
class Geometry
{
	Vertex * _verticesData[NUMBASICOBJECTS];
	int _numVertices[NUMBASICOBJECTS];
	int _currentPlayerObject;
	std::vector <GameObject> _listOfObjects;
	void loadBasic3DObjects();
	void createCube(int _objectType);
	void createPyramid(int _objectType);
	void createPlane(int _objectType);

public:
	Geometry();
	~Geometry();
	int getCurrentPlayerObject();
	void loadGameElements(char fileName[100]);
	Vertex * getData(int objectID);
	int getNumVertices(int objectID);
	int getNumGameElements();
	GameObject & getGameElement(int objectID);
};

