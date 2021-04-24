#include "ConsoleHandler.h"

bool ConsoleHandler::initialize()
{
	// Get the handle
	this->newStdOut = GetStdHandle(STD_ERROR_HANDLE);
	if (this->newStdOut == INVALID_HANDLE_VALUE)
		return false;
	
	// Get the mode
	if (!GetConsoleMode(this->newStdOut, &originalOutMode))
		return false;

	// Set the new mode
	this->outMode = this->originalOutMode | this->REQUESTED_OUT_MODES;
	if (!SetConsoleMode(this->newStdOut, this->outMode))
		return false;

	// Set the buffer to the console handler
	if (!SetConsoleActiveScreenBuffer(this->newStdOut))
		return false;

	// Get the cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	if (!GetConsoleCursorInfo(this->newStdOut, &cursorInfo))
		return false;

	// Make cursor invisible
	cursorInfo.bVisible = false;
	if (!SetConsoleCursorInfo(this->newStdOut, &cursorInfo))
		return false;

	// All is fine - return that everything is ready to go
	return true;
}

void ConsoleHandler::printChars(CHAR_INFO* characters, SHORT x, SHORT y, SHORT lengthX, SHORT lengthY)
{
	SMALL_RECT rect = { 0, 0, lengthX, lengthY };
	WriteConsoleOutputA(this->newStdOut, characters, { lengthX, lengthY }, { x, y }, &rect);
}

void ConsoleHandler::setTitle(LPCSTR title)
{
	SetConsoleTitleA(title);
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