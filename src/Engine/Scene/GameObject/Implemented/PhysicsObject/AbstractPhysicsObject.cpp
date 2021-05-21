#include "AbstractPhysicsObject.h"

AbstractPhysicsObject::AbstractPhysicsObject(
	double posX, double posY, double angle, Scene& scene)
		: AbstractGameObject(posX, posY, angle), SCENE(scene) { }
