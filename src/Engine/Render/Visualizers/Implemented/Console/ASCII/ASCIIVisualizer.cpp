#include "ASCIIVisualizer.h"

void ASCIIVisualizer::visualize(RenderLayerComposer& composer)
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
			int COMPOSER_X_PIXEL = (double)x / WIDTH * COMPOSER_WIDTH;
			int COMPOSER_Y_PIXEL = (double)y / HEIGHT * COMPOSER_HEIGHT;

			FrameBufferPixel pixel = composerResult[COMPOSER_Y_PIXEL][COMPOSER_X_PIXEL];

			int brightness = 7; // (pixel.fogTransparency * pixel.surfaceBrightness * pixel.sectorBrightness) * 
			brightness = min(max(brightness, 0), 7);

			renderResult[y * WIDTH + x].Attributes = (int)pixel.surfaceColor;

			switch (pixel.surfaceType)
			{
				case SurfaceTypes::NONE:
					renderResult[y * WIDTH + x].Attributes = 0;
					renderResult[y * WIDTH + x].Char.AsciiChar = ' ';
					break;
				case SurfaceTypes::CEILING:
					renderResult[y * WIDTH + x].Char.AsciiChar = CEILING_CHAR_LOOKUP[brightness];
					break;
				case SurfaceTypes::SKY:
					renderResult[y * WIDTH + x].Attributes += 8;
					renderResult[y * WIDTH + x].Char.AsciiChar = CEILING_CHAR_LOOKUP[brightness];
					break;
				case SurfaceTypes::FLOOR:
					renderResult[y * WIDTH + x].Attributes += 8;
					renderResult[y * WIDTH + x].Char.AsciiChar = FLOOR_CHAR_LOOKUP[brightness];
					break;
				case SurfaceTypes::PIT:
					renderResult[y * WIDTH + x].Char.AsciiChar = FLOOR_CHAR_LOOKUP[brightness];
					break;
				case SurfaceTypes::WALL_NORTH:
				case SurfaceTypes::WALL_SOUTH:
					renderResult[y * WIDTH + x].Char.AsciiChar = WALL_CHAR_LOOKUP[brightness];
					break;
				case SurfaceTypes::WALL_WEST:
				case SurfaceTypes::WALL_EAST:
					renderResult[y * WIDTH + x].Attributes += 8;
					renderResult[y * WIDTH + x].Char.AsciiChar = WALL_CHAR_LOOKUP[brightness];
					break;
			}
		}
	}

	this->printChars(renderResult, 0, 0, WIDTH, HEIGHT);

	delete[] renderResult;
}
