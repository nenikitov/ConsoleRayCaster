#include "AbstractConsoleRenderer.h"

void AbstractConsoleRenderer::init()
{
	if (this->CONSOLE_HANDLE == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Could not get console handle");

	DWORD originalMode;
	if (!GetConsoleMode(this->CONSOLE_HANDLE, &originalMode))
		throw std::runtime_error("Could not get console mode");

	if (!SetConsoleMode(this->CONSOLE_HANDLE, originalMode | AbstractConsoleRenderer::REQUESTED_OUT_MODES))
		throw std::runtime_error("Could not request console mode");

	if (!SetConsoleActiveScreenBuffer(this->CONSOLE_HANDLE))
		throw std::runtime_error("Could not set console buffer");

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(this->CONSOLE_HANDLE, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(this->CONSOLE_HANDLE, &cursorInfo);
}

void AbstractConsoleRenderer::setTitle(char* title)
{
	SetConsoleTitleA(title);
}

int AbstractConsoleRenderer::getWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(this->CONSOLE_HANDLE, &info);
	return info.srWindow.Right - info.srWindow.Left + 1;
}

int AbstractConsoleRenderer::getHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(this->CONSOLE_HANDLE, &info);
	return info.srWindow.Bottom - info.srWindow.Top + 1;
}
