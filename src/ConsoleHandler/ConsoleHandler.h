#pragma once
#include <Windows.h>

class ConsoleHandler
{
	public:
		bool initialize();
		void printChar(SHORT x, SHORT y, const char* character, WORD attibutes);
	private:
		const DWORD REQUESTED_OUT_MODES = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
		HANDLE newStdOut;
		DWORD originalOutMode = 0;
		DWORD outMode = 0;
};