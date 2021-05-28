#pragma once

#include "../../IVisualizer.h"
#include <Windows.h>
#include <stdexcept>

class AbstractConsoleVisualizer : public IVisualizer
{
	public:
		BufferRequirements getRequirements() override;
		void init() override;
		virtual void visualize(RenderLayerComposer& composer) override = 0;
		void refreshSize() override;
		void setTitle(const char* title) override;
		int getWidth() override;
		int getHeight() override;
	protected:
		void printChars(CHAR_INFO* characters, SHORT x, SHORT y, SHORT lengthX, SHORT lengthY);
	private:
		const BufferRequirements BUFFER_REQUIREMENTS = BufferRequirements(true, false, true, false);
		const DWORD REQUESTED_OUT_MODES = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
		const HANDLE CONSOLE_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
};
