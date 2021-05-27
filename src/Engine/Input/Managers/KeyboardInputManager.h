#pragma once

#include <Windows.h>
#include "../AxisKeys/AxisKeys.h"

class KeyboardInputManager
{
	public:
		static bool getActionKeyState(int key);
		static int getAxisKeyState(AxisKeys keys);
};
