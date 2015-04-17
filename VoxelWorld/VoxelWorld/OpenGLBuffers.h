#pragma once
//Third-party libraries
#include <GL/glew.h>			//The OpenGL Extension Wrangler
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <iostream>
#include "GLSLProgram.h"
#include <cstddef>
#include "Vertex.h"

class OpenGLBuffers {
	GLuint _gVAO;			//Vertex Array Object
	GLuint _gVBO;			//Vertex Buffer Object
	bool _glLinemode;				//Specify if system will render primitives as GL_LINE or GL_FILL

public:
	OpenGLBuffers();
	~OpenGLBuffers();
	void initializeBuffers(GLSLProgram & _colorProgram);
	void allocateVAOVBO();
	void initializeVertexArrayObject(GLSLProgram & _colorProgram);
	void sendDataToGPU(Vertex * data, int numVertex);
	void swapPolygonMode();
};

