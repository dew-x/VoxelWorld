#pragma once
#include <glm/glm.hpp>			//OpenGL Mathematics 


struct GameObject {
	int _objectType;
	glm::vec4 _color;
	bool _textureRepetion;			//It is used to force the texture repetition in a geometric model
	GLuint _textureID;				//Identifier that OpenGL has set to its associated texture
	std::string _textureFile;		//This is the path where the texture is stored
	glm::vec3 _translate;
	float _angle;
	glm::vec3 _rotation;
	glm::vec3 _scale;
	float _angleXYPlane;			//This is the angle in which the object moves in the XY plane
	float _angleXZPlane;			//This is the angle in which the object moves in the XZ plane
};