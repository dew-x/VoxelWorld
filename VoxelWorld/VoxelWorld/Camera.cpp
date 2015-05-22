#include "Camera.h"
#include <iostream>
#include "Utils.h"
#include <string>

/*
* Default constructor
*/
Camera::Camera():	
	_orthographicMode(false),
	_near(0.1f),
	_far(100000.0f),
	_projectionWidth(30.0f),
	_projectionHeight(30.0f),
	_FOV(glm::radians(45.0f)),
	_cameraPos(10.0f, 0.0f, 0.0f),
	_cameraFront(0.0f,0.0f,0.0f),
	_cameraUp(0.0f,0.0f,1.0f),
	_screenHeight(700),
	_screenWidth(700),
	_aspectRatio(_screenWidth / _screenHeight){	
		updateCameraMatrix();
		setPerspectiveProjection();
}

/*
* Destructor
*/
Camera::~Camera()
{
}

/*
* Get the projection transformation matrix 
* @return glm::mat4 is the transformation matrix requested
*/
glm::mat4 Camera::getProjectionMatrix() {
	return _projectionMatrix;
}

/*
* Get the view transformation matrix
* @return glm::mat4 is the transformation matrix requested
*/
glm::mat4 Camera::getViewMatrix() {
	return _viewMatrix;
}

/*
* Replace the camera position and update the view transformation matrix
* @param cameraPos is the new position of the camera
*/
void Camera::setCameraPosition(glm::vec3 & cameraPos) {
	_cameraPos = cameraPos;
	updateCameraMatrix();
}

void Camera::addCameraPosition(glm::vec3 & cameraPos) {
	_cameraPos += cameraPos;
	updateCameraMatrix();
}
/*
* Replace the camera front and update the view transformation matrix
* @param cameraFront is the new position of the camera
*/
void Camera::setCameraFront(glm::vec3 & cameraFront) {
	_cameraFront = cameraFront;
	updateCameraMatrix();
}

/*
* Set up the resolution used by the camera. It also updates the aspect ration
* @param screenHeight is the new height value
* @param screenWidth is the new width value
*/
void Camera::setResolution(float screenHeight, float screenWidth) {
	_screenHeight = screenHeight;
	_screenWidth = screenWidth;
	_aspectRatio=_screenWidth / _screenHeight;
}

/*
* Set up the orthographic projection
*/
void Camera::setOrthographicProjection() {
	_projectionMatrix = glm::ortho(-_projectionWidth / 2, _projectionWidth / 2, -_projectionHeight / 2, _projectionHeight / 2, _near, _far);
	std::cout << " ortografic" << "\n";
}

/*
* Set up the perspective projection
*/
void Camera::setPerspectiveProjection() {
	_projectionMatrix = glm::perspective(_FOV, _aspectRatio, _near, _far);

	const float *pSource = (const float*)glm::value_ptr(_projectionMatrix);
	for (int i = 0; i < 16; ++i)
		std::cout << " " << i << " " << pSource[i] << std::endl;
}

/*
* Updates the view transformation matrix based on the new cameraPos and cameraFront values
*/
void Camera::updateCameraMatrix() {
	glm::vec3 cameraDirection = glm::normalize(_cameraPos - _cameraFront);

	glm::vec3 up = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross( cameraDirection, up));
	_cameraUp = glm::cross(cameraDirection, cameraRight);

	_viewMatrix = glm::lookAt(_cameraFront, _cameraPos, _cameraUp);
	//std::cout << "\n" << "camera pos : " << _cameraPos.x << " " << _cameraPos.y << " " << _cameraPos.z << "\n";
	//std::cout << "\n" << "camera front : " << _cameraFront.x << " " << _cameraFront.y << " " << _cameraFront.z << "\n";
	//std::cout << "\n" << "camera up : " << _cameraUp.x << " " << _cameraUp.y << " " << _cameraUp.z << "\n";
	//std::cout << "From " << Utils::vecToString(_cameraPos) << " to " << Utils::vecToString(_cameraFront) << " - V_AT= " << Utils::vecToString(glm::normalize(_cameraFront - _cameraPos)) << " and  V_UP: " << Utils::vecToString(_cameraUp) << std::endl;
	/*
	_cameraUp = glm::cross(dir, right);
	_viewMatrix = glm::lookAt(_cameraPos, _cameraPos+dir, _cameraUp);
	*/

}

/* 
* Change the current projection matrix from orthographic to perspective or from perspective to orthographic
*/
void Camera::swapProjectionMode() {
	if (_orthographicMode) {
		_orthographicMode = false;
		setPerspectiveProjection();
	}
	else {
		_orthographicMode = true;
		setOrthographicProjection();
	}
}

void Camera::move(int mode) {
	if (mode == 0) {
		_cameraPos.x += 0.1f;
		_cameraFront.x += 0.1f;
	}
	else if (mode == 2) {
		_cameraPos.x -= 0.1f;
		_cameraFront.x -= 0.1f;
	}
	else if (mode == 1) {
		_cameraPos.y += 0.1f;
		_cameraFront.y += 0.1f;
	}
	else if (mode == 3) {
		_cameraPos.y -= 0.1f;
		_cameraFront.y -= 0.1f;
	}

	updateCameraMatrix();
}
void Camera::zoom(int mode) {

}
