#include "Camera.h"

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 45.0f)
	{
		pitch = 45.0f;
	}

	if (pitch < -45.0f)
	{
		pitch = -45.0f;
	}

	update2();
}

glm::mat4 Camera::calculateViewMatrix(bool tipo)
{
	if (tipo)
		return glm::lookAt(position, orientation, up);
	else
		return glm::lookAt(glm::vec3(positionBase.x, positionBase.y + 200, positionBase.z), positionBase, glm::vec3(0.0f, 0.0f, -1.0f));

}

glm::mat4 Camera::calculateViewMatrix2()
{
	return glm::lookAt(glm::vec3(positionBase.x,positionBase.y+200,positionBase.z), positionBase, glm::vec3(0.0f,0.0f,-1.0f));
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}


glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::setOrientation(glm::vec3 posModelo) {
	orientation = posModelo;
}
void Camera::setPosicionBase(glm::vec3 posModelo) {
	positionBase = posModelo;
}
void Camera :: update2() {
	position.x = positionBase.x- (70.0f* sin(glm::radians(pitch)))*cos(glm::radians(yaw));
	position.y = positionBase.y + 0*70.0f* sin(glm::radians(pitch));
	position.z= positionBase.z- (70.0f* sin(glm::radians(pitch)))*sin(glm::radians(yaw));
}
Camera::~Camera()
{
}
