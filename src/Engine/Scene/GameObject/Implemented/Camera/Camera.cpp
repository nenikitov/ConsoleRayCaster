#include "Camera.h"

Camera::Camera(double posX, double posY, double angle, double fov)
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
