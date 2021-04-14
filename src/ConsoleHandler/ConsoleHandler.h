#pragma once
#include <Windows.h>
#include <string>
#include <vector>

class ConsoleHandler
{
	public:
		bool initialize();
		void printChars(CHAR_INFO* characters, SHORT x, SHORT y, SHORT lengthX, SHORT lengthY);
		void setTitle(LPCSTR title);
		int getConsoleWidth();
		int getConsoleHeight();
	private:
		const DWORD REQUESTED_OUT_MODES = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
		HANDLE newStdOut;
		DWORD originalOutMode = 0;
		DWORD outMode = 0;
};