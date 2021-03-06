#include "ShadeVisualizer.h"

void ShadeVisualizer::visualize(RenderLayerComposer& composer)
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
			int COMPOSER_X_PIXEL = int((COMPOSER_WIDTH - 1) * x / (WIDTH - 1.f));
			int COMPOSER_Y_PIXEL = int((COMPOSER_HEIGHT - 1) * y / (HEIGHT - 1.f));

			FrameBufferPixel pixel = composerResult[COMPOSER_Y_PIXEL][COMPOSER_X_PIXEL];

			double surfaceTypeBrightness = 0;
			switch (pixel.surfaceType)
			{
				case SurfaceTypes::SKY:
					surfaceTypeBrightness = 4;
					break;
				case SurfaceTypes::FLOOR:
				case SurfaceTypes::WALL_WEST:
					surfaceTypeBrightness = 1.25;
					break;
				case SurfaceTypes::WALL_NORTH:
				case SurfaceTypes::PIT:
					surfaceTypeBrightness = 1.1;
					break;
				case SurfaceTypes::WALL_SOUTH:
				case SurfaceTypes::CEILING:
					surfaceTypeBrightness = 0.9;
					break;
				case SurfaceTypes::WALL_EAST:
					surfaceTypeBrightness = 0.75;
					break;
			}

			double brightness = 0;
			if (pixel.surfaceReceiveLighting)
				brightness = pixel.fogTransparency * pixel.surfaceBrightness * pixel.sectorBrightness;
			else
				brightness = pixel.surfaceBrightness;

			brightness *= surfaceTypeBrightness;

			const char PIXEL_CHAR = this->lookupChar(brightness);
			const int FG_COLOR = this->lookupFGColor(pixel.surfaceColor, brightness);
			const int BG_COLOR = this->lookupBGColor(pixel.surfaceColor, brightness);

			renderResult[y * WIDTH + x].Attributes = FG_COLOR | (BG_COLOR * 16);
			renderResult[y * WIDTH + x].Char.AsciiChar = PIXEL_CHAR;
		}
	}

	this->printChars(renderResult, 0, 0, WIDTH, HEIGHT);

	delete[] renderResult;
}

int ShadeVisualizer::getLookupIndex(double brightness)
{
	brightness = brightness * 9;
	int lookup = max(min(brightness, 9), 0);

	return lookup;
}

unsigned char ShadeVisualizer::lookupChar(double brightness)
{
	return this->GRADIENT_CHAR_LOOKUP[this->getLookupIndex(brightness)];
}

int ShadeVisualizer::lookupFGColor(SurfaceColors color, double brightness)
{
	int col = this->FG_COLOR_LOOKUP[this->getLookupIndex(brightness)];

	switch (col)
	{
		case 0:
			return 0;
		case 1:
			return (int)color;
		case 2:
			return (int)color + 8;
		default:
			return 0;
	}
}

int ShadeVisualizer::lookupBGColor(SurfaceColors color, double brightness)
{
	int col = this->BG_COLOR_LOOKUP[this->getLookupIndex(brightness)];

	switch (col)
	{
		case 0:
			return 0;
		case 1:
			return (int)color;
		case 2:
			return (int)color + 8;
		default:
			return 0;
	}
}
