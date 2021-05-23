#include "RenderLayerComposer.h"

RenderLayerComposer::RenderLayerComposer(int width, int height)
{
    this->changeDimensions(width, height);
}

void RenderLayerComposer::changeDimensions(int width, int height)
{
    this->width = width;
    this->height = height;


}

void RenderLayerComposer::addRenderLayer(FrameBufferPixel** renderLayer, int renderedWidth, int renderedHeight, double startX, double startY, double endX, double endY)
{
}

FrameBufferPixel** RenderLayerComposer::compose()
{
    return nullptr;
}

void RenderLayerComposer::clearResult()
{
    delete this->compositionResult;

    this->compositionResult = new FrameBufferPixel * [this->height];
    for (int i = 0; i < this->height; i++)
        compositionResult[i] = new FrameBufferPixel[this->width];


}
