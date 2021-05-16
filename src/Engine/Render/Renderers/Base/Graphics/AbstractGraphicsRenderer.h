#pragma once

#include "../../IRenderer.h"

class AbstractGraphicsRenderer : public IRenderer
{
	public:
		BufferRequirements getRequirements() override;
		virtual void init() = 0;
		virtual void render() = 0;
	protected:
		virtual void setTitle(char* title) = 0;
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
	private:
		const BufferRequirements BUFFER_REQUIREMENTS = BufferRequirements(true, true, true, true);
};
