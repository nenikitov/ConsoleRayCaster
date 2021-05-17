#pragma once

#include "../../FrameBuffer/FrameBuffer.h"

class AbstractBufferRenderer
{
	public:
		void changeDimensions(int width, int height);
		virtual FrameBuffer** render() = 0;
	protected:
		int width = 0;
		int height = 0;
};
