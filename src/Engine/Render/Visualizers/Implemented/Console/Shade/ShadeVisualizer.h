#pragma once

#include "../../../Abstract/Console/AbstractConsoleVisualizer.h"

class ShadeVisualizer : public AbstractConsoleVisualizer
{
	public:
		virtual void visualize(RenderLayerComposer& composer) override;
	private:
		const unsigned char GRADIENT_CHAR_LOOKUP[11] = { 32, 176, 177, 178, 176, 32, 176, 177, 178, 176, 219 };
		const char FG_COLOR_LOOKUP[11] = { 1, 1, 1, 1, 0, 2, 2, 2, 2, 1, 2 };
		const char BG_COLOR_LOOKUP[11] = { 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 1 };

		int getLookupIndex(double brightness);
		unsigned char lookupChar(double brightness);
		int lookupFGColor(SurfaceColors color, double brightness);
		int lookupBGColor(SurfaceColors color, double brightness);
};
