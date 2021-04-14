#include "ConsoleHandler.h"

bool ConsoleHandler::initialize()
{
	this->newStdOut = GetStdHandle(STD_ERROR_HANDLE);
	if (this->newStdOut == INVALID_HANDLE_VALUE)
		return false;
	
	if (!GetConsoleMode(this->newStdOut, &originalOutMode))
		return false;

	this->outMode = this->originalOutMode | this->REQUESTED_OUT_MODES;
	if (!SetConsoleMode(this->newStdOut, this->outMode))
		return false;

	if (!SetConsoleActiveScreenBuffer(this->newStdOut))
		return false;

	CONSOLE_CURSOR_INFO cursorInfo;
	if (!GetConsoleCursorInfo(this->newStdOut, &cursorInfo))
		return false;

	cursorInfo.bVisible = false;

	if (!SetConsoleCursorInfo(this->newStdOut, &cursorInfo))
		return false;

	return true;
}

void ConsoleHandler::printChars(const CHAR_INFO* characters, SHORT x, SHORT y, SHORT lengthX, SHORT lengthY)
{
	SMALL_RECT rect = { 0, 0, lengthX, lengthY };
	WriteConsoleOutputA(this->newStdOut, characters, { lengthX, lengthY }, { x, y }, &rect);
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
