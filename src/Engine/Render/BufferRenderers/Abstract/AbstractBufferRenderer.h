#pragma once

#include "../../FrameBuffer/FrameBufferPixel.h"

class AbstractBufferRenderer
{
	public:
		AbstractBufferRenderer(int width, int height);
		void changeDimensions(int width, int height);
		virtual FrameBufferPixel** render() = 0;
	protected:
		int width = 0;
		int height = 0;
};
