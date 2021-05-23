#include "ASCIIVisualizer.h"

void ASCIIVisualizer::render(RenderLayerComposer& composer)
{
	const int WIDTH = this->getWidth();
	const int HEIGHT = this->getHeight();
	FrameBufferPixel** composerResult = composer.compose();
	const int COMPOSER_WIDTH = composer.getWidth() - 1;
	const int COMPOSER_HEIGHT = composer.getHeight() - 1;
	CHAR_INFO* renderResult = new CHAR_INFO[WIDTH * HEIGHT];

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			int COMPOSER_X_PIXEL = (double)x / WIDTH * COMPOSER_WIDTH;
			int COMPOSER_Y_PIXEL = (double)y / HEIGHT * COMPOSER_HEIGHT;

			FrameBufferPixel pixel = composerResult[COMPOSER_Y_PIXEL][COMPOSER_X_PIXEL];
			switch (pixel.surfaceType)
			{
				case SurfaceTypes::NONE:
					renderResult[y * WIDTH + x].Attributes = 1;
					renderResult[y * WIDTH + x].Char.AsciiChar = '.';
					break;
				case SurfaceTypes::CEILING:
				case SurfaceTypes::SKY:
					renderResult[y * WIDTH + x].Attributes = 2;
					renderResult[y * WIDTH + x].Char.AsciiChar = '+';
					break;
				case SurfaceTypes::FLOOR:
				case SurfaceTypes::PIT:
					renderResult[y * WIDTH + x].Attributes = 3;
					renderResult[y * WIDTH + x].Char.AsciiChar = '-';
					break;
				case SurfaceTypes::WALL_NORTH:
				case SurfaceTypes::WALL_SOUTH:
				case SurfaceTypes::WALL_WEST:
				case SurfaceTypes::WALL_EAST:
					renderResult[y * WIDTH + x].Attributes = 4;
					renderResult[y * WIDTH + x].Char.AsciiChar = '#';
					break;
			}
		}
	}

	this->printChars(renderResult, 0, 0, WIDTH, HEIGHT);

	delete renderResult;
}
