#pragma once

#include <corecrt_math.h>
#include "../FrameBuffer/FrameBufferPixel.h"

class RenderLayerComposer
{
	public:
		RenderLayerComposer(int width, int height);
		void changeDimensions(int width, int height);
		void addRenderLayer(FrameBufferPixel** renderLayer, int renderedWidth, int renderedHeight, double startX, double startY, double endX, double endY);
		FrameBufferPixel** compose();
		void clearBuffer();
		int getWidth();
		int getHeight();
	private:
		int width;
		int height;
		void initializeBuffer();
		FrameBufferPixel** compositionResult;
};
