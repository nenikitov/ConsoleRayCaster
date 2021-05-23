#include "RenderLayerComposer.h"

RenderLayerComposer::RenderLayerComposer(int width, int height)
{
    this->changeDimensions(width, height);
}

void RenderLayerComposer::changeDimensions(int width, int height)
{
    this->width = width;
    this->height = height;

    this->clearResult();
}

void RenderLayerComposer::addRenderLayer(FrameBufferPixel** renderLayer, int renderedWidth, int renderedHeight, double startX, double startY, double endX, double endY)
{
    startX = fmax(0, fmin(1, startX));
    startY = fmax(0, fmin(1, endY));
    endX = fmax(0, fmin(1, startX));
    endY = fmax(0, fmin(1, endY));

    const int START_X_PIXEL = startX * this->width;
    const int START_Y_PIXEL = startY * this->height;
    const int END_X_PIXEL = endX * this->width;
    const int END_Y_PIXEL = endY * this->height;

    const int DELTA_X_PIXELS = END_X_PIXEL - START_X_PIXEL;
    const int DELTA_Y_PIXELS = END_Y_PIXEL - START_Y_PIXEL;

    for (int x = 0; x < DELTA_X_PIXELS; x++)
    {
        for (int y = 0; y < DELTA_Y_PIXELS; y++)
        {
            const int RENDER_PIXEL_X = (double)x / DELTA_X_PIXELS;
            const int RENDER_PIXEL_Y = (double)y / DELTA_Y_PIXELS;

            const int COMPOSER_PIXEL_X = x + START_X_PIXEL;
            const int COMPOSER_PIXEL_Y = y + START_Y_PIXEL;

            this->compositionResult[COMPOSER_PIXEL_Y][COMPOSER_PIXEL_X] = renderLayer[RENDER_PIXEL_Y][RENDER_PIXEL_X];
        }
    }
}

FrameBufferPixel** RenderLayerComposer::compose()
{
    return this->compositionResult;
}

int RenderLayerComposer::getWidth()
{
    return this->width;
}

int RenderLayerComposer::getHeight()
{
    return this->height;
}

void RenderLayerComposer::clearResult()
{
    delete this->compositionResult;

    this->compositionResult = new FrameBufferPixel * [this->height];
    for (int i = 0; i < this->height; i++)
        compositionResult[i] = new FrameBufferPixel[this->width];
}
