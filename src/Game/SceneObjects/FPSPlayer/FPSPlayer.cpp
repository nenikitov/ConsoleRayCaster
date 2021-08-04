#include "FPSPlayer.h"

FPSPlayer::FPSPlayer(Scene& scene, double fov) : AbstractPlayer(scene, fov) { }

void FPSPlayer::tick(double deltaTime)
{
	const int FORWARD_INPUT = KeyboardInputManager::getAxisKeyState({ 'W', 'S' });
	const int RIGHTWARD_INPUT = KeyboardInputManager::getAxisKeyState({ 'D', 'A' });
	const int TURN_INPUT = KeyboardInputManager::getAxisKeyState({ VK_RIGHT, VK_LEFT });

	// Update rotation if player input is received
	if (TURN_INPUT != 0)
	{
		const double TURN_SEPPED = 2 * deltaTime;
		
		this->angle += TURN_INPUT * TURN_SEPPED;
		if (this->angle < 0)
			this->angle = 2 * 3.141592 + angle;
		else if (this->angle >= 2 * 3.141592)
			this->angle = fmod(this->angle, 2 * 3.141592);
	}

	// Update location if player input is received
	if (FORWARD_INPUT != 0 || RIGHTWARD_INPUT != 0)
	{
		const double MOVEMENT_SPEED = 2 * deltaTime;
		
		// Move along X axis
		const double DELTA_X = MOVEMENT_SPEED * (cos(this->angle) * FORWARD_INPUT - sin(this->angle) * RIGHTWARD_INPUT);
		this->moveAlongAxis(true, DELTA_X);

		// Move along Y axis
		const double DELTA_Y = MOVEMENT_SPEED * (sin(this->angle) * FORWARD_INPUT + cos(this->angle) * RIGHTWARD_INPUT);
		this->moveAlongAxis(false, DELTA_Y);
	}

	// Move camera with the player
	this->camera.setTransform(this->posX, this->posY, this->angle);
}

void FPSPlayer::moveAlongAxis(bool x, double delta)
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
	else
	{
		double INTERSECTION_LOCATION = x ? intersection.X : intersection.Y;
		double RADIUS_CORRECTION = (delta > 0) ? -this->RADIUS : this->RADIUS;

		pos = INTERSECTION_LOCATION + RADIUS_CORRECTION;
	}
}
