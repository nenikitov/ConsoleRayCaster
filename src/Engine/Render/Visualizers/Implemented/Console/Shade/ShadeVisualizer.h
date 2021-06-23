#pragma once

#include "../../../Abstract/Console/AbstractConsoleVisualizer.h"

class ShadeVisualizer : public AbstractConsoleVisualizer
{
	public:
		virtual void visualize(RenderLayerComposer& composer) override;
	private:
		const char GRADIENT_CHAR_LOOKUP[11] = { 219,  176, 178, 177, 176, 32, 176, 178, 177, 176, 32 };
		const char FG_COLOR_LOOKUP[11] = { 2, 1, 2, 2, 2, 2, 0, 1, 1, 1, 1 };
		const char BG_COLOR_LOOKUP[11] = { 1, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0 };

		int getLookupIndex(double brightness);
		char lookupChar(double brightness);
		int lookupFGColor(SurfaceColors color, double brightness);
		int lookupBGColor(SurfaceColors color, double brightness);
};
