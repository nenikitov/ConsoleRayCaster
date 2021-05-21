#include "AbstractPlayer.h"

AbstractPlayer::AbstractPlayer(Scene& scene, double fov)
	: AbstractPhysicsObject(scene.getPlayerStartX(), scene.getPlayerStartY(), scene.getPlayerStartAngle()),
	CAMERA(Camera(this->posX, this->posY, this->angle, fov)) { }
