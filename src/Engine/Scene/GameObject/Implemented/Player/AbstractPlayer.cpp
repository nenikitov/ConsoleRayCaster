#include "AbstractPlayer.h"

AbstractPlayer::AbstractPlayer(
	double posX, double posY, double angle, Scene& scene)
		: AbstractGameObject(posX, posY, angle), SCENE(scene) { }
