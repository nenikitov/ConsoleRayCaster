#pragma once

#include "../../FrameBuffer/FrameBuffer.h"

class AbstractBufferRenderer
{
	public:
		void changeDimensions(int startX, int startY, int width, int height);
		virtual FrameBuffer** render() = 0;
	protected:
		int startX = 0;
		int startY = 0;
		int width  = 0;
		int height = 0;
};
