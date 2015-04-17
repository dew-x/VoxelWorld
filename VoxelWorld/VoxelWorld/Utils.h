#pragma once
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <string>

class Utils
{
public:
	Utils();
	~Utils();
	static std::string vecToString(glm::vec3 & dataVector);
	static void drawMatrix(glm::mat4 & dataMatrix);
};

