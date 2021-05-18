#pragma once

#include "../BufferRequirements/BufferRequirements.h"

class IBufferVisualizer
{
	public:
		virtual BufferRequirements getRequirements() = 0;
		virtual void init()                          = 0;
		virtual void render()                        = 0;
	protected:
		virtual void setTitle(char* title) = 0;
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
};