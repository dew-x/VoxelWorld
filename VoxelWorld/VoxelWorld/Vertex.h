#pragma once
//Third-party libraries
#include <GL/glew.h>			//The OpenGL Extension Wrangler
#include <glm/glm.hpp>			//OpenGL Mathematics 

struct Position {
	GLfloat  x;
	GLfloat  y;
	GLfloat  z;
};

struct ColorRGBA8 {
	ColorRGBA8() :r(0), g(0), b(0), a(0) {	}
	ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A)  {}
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct UV {
	GLfloat u;
	GLfloat v;
};

struct Vertex {
	Position position;
	GLfloat id;
	ColorRGBA8 color;
	UV uv;
	Position normal;

	void setPosition(GLfloat  x, GLfloat  y, GLfloat  z) {
		position.x = x;
		position.y = y;
		position.z = z;
	}
	
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void setUV(float u, float v) {
		uv.u = u;
		uv.v = v;
	}

	void setId(GLint id) {
		this->id = id;
	}

	void setNormal(GLfloat x, GLfloat y, GLfloat z){
		normal.x = x;
		normal.y = y;
		normal.z = z;
	}
};