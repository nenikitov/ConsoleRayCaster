#include "RenderLayerComposer.h"

RenderLayerComposer::RenderLayerComposer(int width, int height)
{
    this->changeDimensions(width, height);
}

void RenderLayerComposer::changeDimensions(int width, int height)
{
    this->clearBuffer();

    this->width = width;
    this->height = height;

    this->initializeBuffer();
}

void RenderLayerComposer::addRenderLayer(FrameBufferPixel** renderLayer, int renderedWidth, int renderedHeight, double startX, double startY, double endX, double endY)
{
    startX = fmax(0, fmin(1, startX));
    startY = fmax(0, fmin(1, startY));
    endX = fmax(0, fmin(1, endX));
    endY = fmax(0, fmin(1, endY));

    const int START_X_PIXEL = startX * ((double)this->width - 1);
    const int START_Y_PIXEL = startY * ((double)this->height - 1);
    const int END_X_PIXEL = endX * ((double)this->width - 1);
    const int END_Y_PIXEL = endY * ((double)this->height - 1);

    const int DELTA_X_PIXELS = END_X_PIXEL - START_X_PIXEL;
    const int DELTA_Y_PIXELS = END_Y_PIXEL - START_Y_PIXEL;

    for (int y = 0; y < DELTA_Y_PIXELS; y++)
    {
        for (int x = 0; x < DELTA_X_PIXELS; x++)
        {
            const int RENDER_PIXEL_X = (double)x / DELTA_X_PIXELS * ((double)renderedWidth - 1);
            const int RENDER_PIXEL_Y = (double)y / DELTA_Y_PIXELS * ((double)renderedHeight - 1);

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

void RenderLayerComposer::initializeBuffer()
{
    this->compositionResult = new FrameBufferPixel*[this->height];
    for (int i = 0; i < this->height; i++)
        compositionResult[i] = new FrameBufferPixel[this->width];
}

void RenderLayerComposer::clearBuffer()
{
    for (int i = 0; i < this->height; i++)
        delete this->compositionResult[i];

    delete this->compositionResult;
}