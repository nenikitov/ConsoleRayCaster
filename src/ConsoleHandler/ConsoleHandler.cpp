#include "ConsoleHandler.h"

bool ConsoleHandler::initialize()
{
	this->newStdOut = GetStdHandle(STD_ERROR_HANDLE);
	if (newStdOut == INVALID_HANDLE_VALUE)
		return false;
	
	if (!GetConsoleMode(newStdOut, &originalOutMode))
		return false;

	this->outMode = this->originalOutMode | this->REQUESTED_OUT_MODES;
	if (!SetConsoleMode(this->newStdOut, this->outMode))
		return false;

	return true;
}

void ConsoleHandler::printChar(SHORT x, SHORT y, const char* character, WORD attibutes)
{
	COORD coords;
	coords.X = x;
	coords.Y = y;

	WORD lAttributes = attibutes;
	DWORD written;

	WriteConsoleOutputAttribute(this->newStdOut, &lAttributes, 1, coords, &written);
	WriteConsoleOutputCharacterA(this->newStdOut, character, 1, coords, &written);
}