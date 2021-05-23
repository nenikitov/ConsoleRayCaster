#include "ASCIIVisualizer.h"

void ASCIIVisualizer::render(RenderLayerComposer& composer)
{
	const int WIDTH = this->getWidth();
	const int HEIGHT = this->getHeight();
	FrameBufferPixel** composerResult = composer.compose();
	const int COMPOSER_WIDTH = composer.getWidth();
	const int COMPOSER_HEIGHT = composer.getHeight();
	CHAR_INFO* renderResult = new CHAR_INFO[WIDTH * HEIGHT];

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			const int COMPOSER_X_PIXEL = (double)x / WIDTH * COMPOSER_WIDTH;
			const int COMPOSER_Y_PIXEL = (double)y / HEIGHT * COMPOSER_HEIGHT;

			const FrameBufferPixel pixel = composerResult[y][x];

			switch (pixel.surfaceType)
			{
				case SurfaceTypes::NONE:
					renderResult[y * WIDTH + x].Attributes = 1;
					renderResult[y * WIDTH + x].Char.AsciiChar = ' ';
					break;
				case SurfaceTypes::CEILING:
				case SurfaceTypes::SKY:
					renderResult[y * WIDTH + x].Attributes = 1;
					renderResult[y * WIDTH + x].Char.AsciiChar = ' ';
					break;
				case SurfaceTypes::FLOOR:
				case SurfaceTypes::PIT:
					renderResult[y * WIDTH + x].Attributes = 1;
					renderResult[y * WIDTH + x].Char.AsciiChar = ' ';
					break;
				case SurfaceTypes::WALL_NORTH:
				case SurfaceTypes::WALL_SOUTH:
				case SurfaceTypes::WALL_WEST:
				case SurfaceTypes::WALL_EAST:
					renderResult[y * WIDTH + x].Attributes = (WORD) SurfaceColors::BLUE;
					renderResult[y * WIDTH + x].Char.AsciiChar = '#';
					break;
			}
		}
	}

	delete renderResult;
}
