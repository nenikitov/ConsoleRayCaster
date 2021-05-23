#pragma once

#include "../../../Abstract/Console/AbstractConsoleVisualizer.h"

class ASCIIVisualizer : public AbstractConsoleVisualizer
{
	public:
		virtual void render(RenderLayerComposer& composer) override;
	private:
		const char WALL_CHAR_LOOKUP[8] = { '.',  ':', ';', '+', '=', 'x', 'X', '#' };
		const char FLOOR_CHAR_LOOKUP[8] = { '`', '\'', '"', '<', 'f', '?', '8', '@' };
		const char CEILING_CHAR_LOOKUP[8] = { '.',  '-', '_', '(', '7', '}', 'E', '%' };
};
