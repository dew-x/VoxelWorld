#pragma once
#include <GL\glew.h>
#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera
{
protected:
	glm::mat4x4 *ViewMatrix, *ViewMatrixInverse;

public:
	glm::vec3 X, Y, Z, Position, Reference;

	Camera();
	~Camera();

	void Look(const glm::vec3 &Position, const glm::vec3 &Reference, bool RotateAroundReference = false);
	void Move(const glm::vec3 &Movement);
	glm::vec3 OnKeys(BYTE Keys, float FrameTime); // arreglar
	void OnMouseMove(int dx, int dy); // arreglar
	void OnMouseWheel(float zDelta); // arreglar
	void SetViewMatrixPointer(float *ViewMatrix, float *ViewMatrixInverse = NULL);

private:
	void CalculateViewMatrix();
};