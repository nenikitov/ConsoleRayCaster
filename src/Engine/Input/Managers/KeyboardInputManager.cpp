#include "KeyboardInputManager.h"

bool KeyboardInputManager::getActionKeyState(int key)
{
    return (bool)GetAsyncKeyState(key);
}

int KeyboardInputManager::getAxisKeyState(AxisKeys keys)
{
    return (bool)GetAsyncKeyState(keys.positiveKey) - (bool)GetAsyncKeyState(keys.oppositeKey);
}
