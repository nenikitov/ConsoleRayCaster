#pragma once

#include "../BufferRequirements/BufferRequirements.h"
#include "../RenderLayerComposer/RenderLayerComposer.h"

class IVisualizer
{
	public:
		virtual BufferRequirements getRequirements() = 0;
		virtual void init() = 0;
		virtual void visualize(RenderLayerComposer& composer) = 0;
		virtual void refreshSize() = 0;
		virtual void setTitle(const char* title) = 0;
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
};
