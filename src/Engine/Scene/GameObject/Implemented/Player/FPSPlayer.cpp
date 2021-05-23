#include "FPSPlayer.h"

FPSPlayer::FPSPlayer(Scene& scene, double fov) : AbstractPlayer(scene, fov) { }

void FPSPlayer::tick(double deltaTime)
{
	const int FORWARD_INPUT = KeyboardInputManager::getAxisKeyState({ 'W', 'S' });
	const int RIGHTWARD_INPUT = KeyboardInputManager::getAxisKeyState({ 'A', 'D' });
	const int TURN_INPUT = KeyboardInputManager::getAxisKeyState({ VK_RIGHT, VK_LEFT });

	// Update position (Implement collision detection later)
	const double movementSpeed = 2 * deltaTime;
	this->posX += movementSpeed * (cos(this->angle) * FORWARD_INPUT - sin(this->angle) * RIGHTWARD_INPUT);
	this->posY += movementSpeed * (sin(this->angle) * FORWARD_INPUT + cos(this->angle) * RIGHTWARD_INPUT);

	// Update rotation
	this->angle += TURN_INPUT * 2 * deltaTime;
	if (this->angle < 0)
		this->angle = 2 * 3.141592 + angle;
	else if (this->angle >= 2 * 3.141592)
		this->angle = fmod(this->angle, 2 * 3.141592);
}
