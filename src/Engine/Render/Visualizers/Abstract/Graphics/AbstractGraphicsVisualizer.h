#pragma once

#include "../../IVisualizer.h"

class AbstractGraphicsVisualizer : public IVisualizer
{
	public:
		BufferRequirements getRequirements() override;
		virtual void init() override = 0;
		virtual void visualize(RenderLayerComposer& composer) override = 0;
	protected:
		virtual void setTitle(char* title) = 0;
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
	private:
		const BufferRequirements BUFFER_REQUIREMENTS = BufferRequirements(true, true, true, true);
};
