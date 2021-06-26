#include "AbstractVisualizer.h"

BufferRequirements AbstractVisualizer::getRequirements()
{
	return this->BUFFER_REQUIREMENTS;
}

void AbstractVisualizer::init()
{
	if (this->CONSOLE_HANDLE == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Could not get console handle");

	DWORD originalMode;
	if (!GetConsoleMode(this->CONSOLE_HANDLE, &originalMode))
		throw std::runtime_error("Could not get console mode");

	if (!SetConsoleMode(this->CONSOLE_HANDLE, originalMode | this->REQUESTED_OUT_MODES))
		throw std::runtime_error("Could not request console mode");

	if (!SetConsoleActiveScreenBuffer(this->CONSOLE_HANDLE))
		throw std::runtime_error("Could not set console buffer");

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(this->CONSOLE_HANDLE, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(this->CONSOLE_HANDLE, &cursorInfo);
}

void AbstractVisualizer::refreshSize()
{
	system("cls");
}

void AbstractVisualizer::setTitle(const char* title)
{
	SetConsoleTitleA(title);
}

int AbstractVisualizer::getWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(this->CONSOLE_HANDLE, &info);
	return info.srWindow.Right - info.srWindow.Left + 1;
}

int AbstractVisualizer::getHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(this->CONSOLE_HANDLE, &info);
	return info.srWindow.Bottom - info.srWindow.Top + 1;
}

void AbstractVisualizer::printChars(CHAR_INFO* characters, SHORT x, SHORT y, SHORT lengthX, SHORT lengthY)
{
	SMALL_RECT rect = { 0, 0, lengthX, lengthY };
	WriteConsoleOutputA(this->CONSOLE_HANDLE, characters, { lengthX, lengthY }, { x, y }, &rect);
}
