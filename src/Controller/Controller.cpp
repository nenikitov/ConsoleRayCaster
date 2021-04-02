#include "Controller.h"

char Controller::getForward()
{
    return GetAsyncKeyState(this->FORWARD_KEY) - GetAsyncKeyState(this->BACKWARD_KEY);
}
char Controller::getRightward()
{
    return GetAsyncKeyState(this->RIGHTWARD_KEY) - GetAsyncKeyState(this->LEFTWARD_KEY);
}
char Controller::getTurn()
{
    return GetAsyncKeyState(this->TURN_RIGHT_KEY) - GetAsyncKeyState(this->TURN_LEFT_KEY);
}