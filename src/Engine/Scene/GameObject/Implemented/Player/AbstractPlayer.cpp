#include "AbstractPlayer.h"

AbstractPlayer::AbstractPlayer(Scene& scene, double fov)
	: AbstractPhysicsObject(scene.getPlayerStartX(), scene.getPlayerStartY(), scene.getPlayerStartAngle(), scene),
	CAMERA(Camera(this->posX, this->posY, this->angle, fov)) { }

