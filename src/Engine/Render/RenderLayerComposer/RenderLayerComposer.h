#pragma once

#include "../FrameBuffer/FrameBufferPixel.h"
#include <corecrt_math.h>

class RenderLayerComposer
{
	public:
		RenderLayerComposer(int width, int height);
		void changeDimensions(int width, int height);
		void addRenderLayer(FrameBufferPixel** renderLayer, int renderedWidth, int renderedHeight, double startX, double startY, double endX, double endY);
		FrameBufferPixel** compose();
		int getWidth();
		int getHeight();
	private:
		void clearResult();
		int width;
		int height;
		FrameBufferPixel** compositionResult;
};
