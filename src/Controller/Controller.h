#pragma once
#include <WinUser.h>

class Controller
{
	public:
		char getForward();
		char getRightward();
		char getTurn();
	private:
		unsigned const short FORWARD_KEY    = 0x57;     // W
		unsigned const short BACKWARD_KEY   = 0x53;     // S
		unsigned const short RIGHTWARD_KEY  = 0x44;     // A
		unsigned const short LEFTWARD_KEY   = 0x41;     // D
		unsigned const short TURN_RIGHT_KEY = VK_RIGHT; // Right arrow
		unsigned const short TURN_LEFT_KEY  = VK_LEFT;  // Left arrow
};