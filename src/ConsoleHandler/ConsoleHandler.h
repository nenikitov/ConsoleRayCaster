#pragma once
#include <Windows.h>
#include <string>
#include <vector>

class ConsoleHandler
{
	public:
		/// <summary>
		/// Initialize the console handler
		/// </summary>
		/// <returns>If it can be initialized</returns>
		bool initialize();
		/// <summary>
		/// Print the rectangle of characters
		/// </summary>
		/// <param name="characters">Character buffer</param>
		/// <param name="x">Start X coordinate</param>
		/// <param name="y">Start Y coordinate</param>
		/// <param name="lengthX">The length of the buffer</param>
		/// <param name="lengthY">The height of the buffer</param>
		void printChars(CHAR_INFO* characters, SHORT x, SHORT y, SHORT lengthX, SHORT lengthY);
		/// <summary>
		/// Set the title of the console window
		/// </summary>
		/// <param name="title">Target title</param>
		void setTitle(LPCSTR title);
		/// <summary>
		/// Get the width of the console
		/// </summary>
		/// <returns>The width of the console (in characters)</returns>
		int getConsoleWidth();
		/// <summary>
		/// Get the height of the console
		/// </summary>
		/// <returns>The height of the console (in characters)</returns>
		int getConsoleHeight();
	private:
		const DWORD REQUESTED_OUT_MODES = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
		HANDLE newStdOut;
		DWORD originalOutMode = 0;
		DWORD outMode = 0;
};