#include "AbstractPhysicsObject.h"

AbstractPhysicsObject::AbstractPhysicsObject(
	double posX, double posY, double angle, double radius, Scene& scene)
		: AbstractGameObject(posX, posY, angle), scene(scene), RADIUS(radius) { }

void AbstractPhysicsObject::moveBy(double deltaX, double deltaY)
{
	this->moveAlongAxis(true, deltaX);
	this->moveAlongAxis(false, deltaY);
}

void AbstractPhysicsObject::moveAlongAxis(bool x, double delta)
{
	const double AXIS_ANGLE = x ? 0 : 1.57079632679;
	const double DIRECTION_ANGLE = (delta > 0) ? AXIS_ANGLE : (AXIS_ANGLE + 3.14159265359);
	double& pos = x ? this->posX : this->posY;

	// Find the wall to the direction
	Intersection intersection = RayCaster::trace(
		this->scene,
		this->posX,
		this->posY,
		DIRECTION_ANGLE);

	if (!intersection.VALID)
	{
		pos += delta;
		return;
	}

	if (intersection.DISTANCE > this->RADIUS)
		pos += delta;
}
