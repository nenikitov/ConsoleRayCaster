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

	CONSOLE_CURSOR_INFO cursorInfo;
	if (!GetConsoleCursorInfo(this->newStdOut, &cursorInfo))
		return false;

	cursorInfo.bVisible = false;

	if (!SetConsoleCursorInfo(this->newStdOut, &cursorInfo))
		return false;

	return true;
}

void ConsoleHandler::printChars(SHORT x, SHORT y, const char* characters, const WORD* attributes, DWORD length)
{
	COORD coords;
	coords.X = x;
	coords.Y = y;

	DWORD written;

	WriteConsoleOutputCharacterA(this->newStdOut, characters, length, coords, &written);
	WriteConsoleOutputAttribute(this->newStdOut, attributes, length, coords, &written);
}

int ConsoleHandler::getConsoleWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(this->newStdOut, &info);
	return info.srWindow.Right - info.srWindow.Left + 1;
}

int ConsoleHandler::getConsoleHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(this->newStdOut, &info);
	return info.srWindow.Bottom - info.srWindow.Top + 1;
}
