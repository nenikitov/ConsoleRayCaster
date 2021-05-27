#include "AbstractBufferRenderer.h"

AbstractBufferRenderer::AbstractBufferRenderer(int width, int height)
{
	this->changeDimensions(width, height);
}

void AbstractBufferRenderer::changeDimensions(int width, int height)
{
	this->width = width;
	this->height = height;
}

int AbstractBufferRenderer::getWidth()
{
	return this->width;
}

int AbstractBufferRenderer::getHeight()
{
	return this->height;
}
