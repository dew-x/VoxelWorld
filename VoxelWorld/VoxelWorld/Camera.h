#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#define CAMERA_SPEED 0.2f


class Camera
{
private:
	float _screenHeight;
	float _screenWidth;
	float _aspectRatio;
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	bool _orthographicMode;
	float _FOV;
	float _far;
	float _near;
	float _projectionWidth;
	float _projectionHeight;
	glm::vec3 _cameraPos;
	glm::vec3 _cameraFront;
	glm::vec3 _cameraUp;
	glm::vec3 _cameraDir;
	glm::vec3 _cameraRight;
		//Internal methods
	void setOrthographicProjection();
	void setPerspectiveProjection();

public:
	Camera();
	~Camera();
		//Get view and projection matrices
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
		//Exchange the projection mode
	void swapProjectionMode();
		//Methods for updating the Camera values
	void updateCameraMatrix();
	void setCameraFront(glm::vec3 & cameraFront);
	void setCameraPosition(glm::vec3 & cameraPos);
	void setCameraUp(glm::vec3 & cameraUp);
	void setResolution(float screenHeight, float screenWidth);
	void move(int mode);
	void zoom(int mode);
};

