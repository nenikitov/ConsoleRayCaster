#include "Controller.h"

char Controller::getForward()
{
    return (bool)GetAsyncKeyState(this->FORWARD_KEY) - (bool)GetAsyncKeyState(this->BACKWARD_KEY);
}
char Controller::getRightward()
{
    return (bool)GetAsyncKeyState(this->RIGHTWARD_KEY) - (bool)GetAsyncKeyState(this->LEFTWARD_KEY);
}
char Controller::getTurn()
{
    return (bool)GetAsyncKeyState(this->TURN_RIGHT_KEY) - (bool)GetAsyncKeyState(this->TURN_LEFT_KEY);
}