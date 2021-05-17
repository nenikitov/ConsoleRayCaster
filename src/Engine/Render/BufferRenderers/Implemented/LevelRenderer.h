#pragma once

#include "../IBufferRenderer.h"

class LevelRenderer : public IBufferRenderer
{
	public:
		LevelRenderer();
		FrameBuffer** render(int width, int height) override;
	private:

};
