#pragma once

#include "../FrameBuffer/FrameBuffer.h"

class IBufferRenderer
{
	public:
		virtual FrameBuffer** render(int width, int height) = 0;
};
