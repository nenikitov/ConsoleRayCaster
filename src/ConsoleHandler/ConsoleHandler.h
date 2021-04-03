#pragma once
#include <Windows.h>
#include <string>
#include <vector>

class ConsoleHandler
{
	public:
		bool initialize();
		void printChars(SHORT x, SHORT y, const char* characters, DWORD length, WORD attributes);
		int getConsoleWidth();
		int getConsoleHeight();
	private:
		const DWORD REQUESTED_OUT_MODES = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
		HANDLE newStdOut;
		DWORD originalOutMode = 0;
		DWORD outMode = 0;
};