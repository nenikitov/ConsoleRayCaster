#include "Camera.h"

Camera::Camera(double fov, double posX, double posY, double angle)
	: AbstractGameObject(posX, posY, angle)
{
	this->fov = fov;
}

double Camera::getFov()
{
	return this->fov;
}

void Camera::setFov(double fov)
{
	this->fov = fov;
}
