#include "AbstractBufferRenderer.h"

void AbstractBufferRenderer::changeDimensions(int startX, int startY, int width, int height)
{
	this->startX = startX;
	this->startY = startY;
	this->width  = width;
	this->height = height;
}
