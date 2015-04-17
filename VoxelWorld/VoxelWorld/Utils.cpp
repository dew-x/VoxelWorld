#include "Utils.h"
#include <stdio.h>			//sprintf
#include <iostream>

Utils::Utils()
{
}


Utils::~Utils()
{
}

/**
* Converts a vector into a string
* @param dataVector is the vector
* @return the string representation
*/
std::string Utils::vecToString(glm::vec3 & dataVector) {
	char temp[100];
	sprintf_s(temp, "(%.2g , %.2g, %.2g)", dataVector.x, dataVector.y, dataVector.z);
	std::string temp2 = temp;	
	return temp2;
}

/*
* Print the content of a matrix
* @param dataMat is the matrix to print
*/
void Utils::drawMatrix(glm::mat4 & dataMatrix) {
	std::cout << std::endl;
	for (int q = 0; q < 4; q++) {
		for (int r = 0; r < 4; r++) {
			std::cout << dataMatrix[q][r] << " ";
		}
		std::cout << std::endl;
	}
}