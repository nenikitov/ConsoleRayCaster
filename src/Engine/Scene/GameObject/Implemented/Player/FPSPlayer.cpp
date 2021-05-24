#include "FPSPlayer.h"

FPSPlayer::FPSPlayer(Scene& scene, double fov) : AbstractPlayer(scene, fov) { }

void FPSPlayer::tick(double deltaTime)
{
	const int FORWARD_INPUT = KeyboardInputManager::getAxisKeyState({ 'W', 'S' });
	const int RIGHTWARD_INPUT = KeyboardInputManager::getAxisKeyState({ 'D', 'A' });
	const int TURN_INPUT = KeyboardInputManager::getAxisKeyState({ VK_RIGHT, VK_LEFT });

	// Update position (Implement collision detection later)
	const double MOVEMENT_SPEED = 1.2 * deltaTime;
	this->posX += MOVEMENT_SPEED * (cos(this->angle) * FORWARD_INPUT - sin(this->angle) * RIGHTWARD_INPUT);
	this->posY += MOVEMENT_SPEED * (sin(this->angle) * FORWARD_INPUT + cos(this->angle) * RIGHTWARD_INPUT);

	// Update rotation
	const double TURN_SEPPED = 1.2 * deltaTime;
	this->angle += TURN_INPUT * TURN_SEPPED;
	if (this->angle < 0)
		this->angle = 2 * 3.141592 + angle;
	else if (this->angle >= 2 * 3.141592)
		this->angle = fmod(this->angle, 2 * 3.141592);

	// Move camera with the player
	this->camera.setTransform(this->posX, this->posY, this->angle);
}
