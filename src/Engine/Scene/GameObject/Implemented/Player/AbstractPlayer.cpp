#include "AbstractPlayer.h"

AbstractPlayer::AbstractPlayer(Scene& scene, double fov)
	: AbstractPhysicsObject(scene.getPlayerStartX(), scene.getPlayerStartY(), scene.getPlayerStartAngle(), scene),
	camera(Camera(this->posX, this->posY, this->angle, fov)) { }

Camera& AbstractPlayer::getCamera()
{
	return this->camera;
}

