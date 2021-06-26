#pragma once

#include "../../BufferRequirements/BufferRequirements.h"
#include "../../RenderLayerComposer/RenderLayerComposer.h"
#include <Windows.h>
#include <stdexcept>

class AbstractVisualizer
{
	public:
		BufferRequirements getRequirements();
		void init();
		virtual void visualize(RenderLayerComposer& composer) = 0;
		void refreshSize();
		void setTitle(const char* title);
		int getWidth();
		int getHeight();
	protected:
		void printChars(CHAR_INFO* characters, SHORT x, SHORT y, SHORT lengthX, SHORT lengthY);
	private:
		const BufferRequirements BUFFER_REQUIREMENTS = BufferRequirements(true, false, true, false);
		const DWORD REQUESTED_OUT_MODES = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
		const HANDLE CONSOLE_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
};
