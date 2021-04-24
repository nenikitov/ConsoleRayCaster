#pragma once
#include <Windows.h>

class Controller
{
	public:
		/// <summary>
		/// Get the axis value of the forward input
		/// </summary>
		/// <returns>The value of the forward input (-1 backward, 0 nothing, and 1 forward)</returns>
		char getForward();
		/// <summary>
		/// Get the axis value of the rightward input
		/// </summary>
		/// <returns>The value of the rightward input (-1 lefrward, 0 nothing, and 1 rightward)</returns>
		char getRightward();
		/// <summary>
		/// Get the axis value of the turn input
		/// </summary>
		/// <returns>The value of the turn input (-1 turn left, 0 nothing, and 1 turn rights)</returns>
		char getTurn();
	private:
		unsigned const short FORWARD_KEY    = 0x57;     // W
		unsigned const short BACKWARD_KEY   = 0x53;     // S
		unsigned const short RIGHTWARD_KEY  = 0x44;     // A
		unsigned const short LEFTWARD_KEY   = 0x41;     // D
		unsigned const short TURN_RIGHT_KEY = VK_RIGHT; // Right arrow
		unsigned const short TURN_LEFT_KEY  = VK_LEFT;  // Left arrow
};