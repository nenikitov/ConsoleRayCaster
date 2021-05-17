#pragma once

#include "../Abstract/AbstractBufferRenderer.h"

class LevelRenderer : public AbstractBufferRenderer
{
	public:
		LevelRenderer();
		FrameBuffer** render() override;
	private:

};
