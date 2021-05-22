#include "SceneRenderer.h"

SceneRenderer::SceneRenderer(int width, int height, Scene& scene, Camera& camera)
	: AbstractBufferRenderer(width, height), scene(scene), camera(camera) { }

FrameBufferPixel** SceneRenderer::render()
{
	#pragma region Precalculate and initialize needed values for the whole render
	const double HALF_HEIGHT = this->height / 2.f;
	const double HALF_H_FOV = this->camera.getFov() / 2.f;
	const double HALF_V_FOV = HALF_H_FOV / (double)this->width * (double)this->height / 2.f;
	const int WALL_HEIGHT = this->width / pow(2, this->camera.getFov()) / 2;
	const double PERPENDICULAR_LENGTH = width / 2.f / tan(HALF_H_FOV);
	FrameBufferPixel** renderResult = new FrameBufferPixel*[this->height];
	for (int i = 0; i < this->height; i++)
		renderResult[i] = (FrameBufferPixel*) malloc(this->width * sizeof(FrameBufferPixel));
	#pragma endregion

	#pragma region Render column by column
	for (int x = 0; x < this->width; x++)
	{
		#pragma region Precalculate and initialize needed values for the current column
		const double RAY_PX_OFFSET = (double)x - this->width / 2.f;
		const double RAY_H_ANGLE = atan(RAY_PX_OFFSET / PERPENDICULAR_LENGTH);
		#pragma endregion

		#pragma region Find intersection
		Intersection intersection = RayCaster::trace(
			this->scene,
			this->camera.getPosX(),
			this->camera.getPosY(),
			this->camera.getAngle() + RAY_H_ANGLE);
		#pragma endregion

		#pragma region Render from intersection
		if (intersection.VALID)
		{
			// Intersection happened, render walls, floor and ceiling
			#pragma region Precalculate and initialize needed values for the current intersection
			const double DELTA_X = intersection.X - this->camera.getPosX();
			const double DELTA_Y = intersection.Y - this->camera.getPosY();
			// Calculate the distance in relation to the camera to fix fisheye effect
			const double CORRECTED_DISTANCE = cos(this->camera.getAngle() * DELTA_X + sin(this->camera.getAngle()) * DELTA_Y);
			// The height of a texel where floor, ceiling and wall should start
			const int PERCEIVED_WALL_HEIGHT = abs(WALL_HEIGHT / CORRECTED_DISTANCE);
			const double CEILING_END = (this->height - PERCEIVED_WALL_HEIGHT) / 2.f;
			const int FLOOR_START = CEILING_END + this->height;
			// Counter for void renderer
			int lastTexturedFloor = -1;
			#pragma endregion

			#pragma region Render pixel by pixel vertically
			for (int y = 0; y < this->height; y++)
			{
				if (y < CEILING_END)
				{
					#pragma region Ceiling rendering
					#pragma endregion
				}
				else if (y > FLOOR_START)
				{
					#pragma region Floor rendering
					#pragma endregion
				}
				else
				{
					#pragma region Wall Rendering
					FrameBufferPixel pixelRenderer = this->renderSurfaceWall(y, CEILING_END, PERCEIVED_WALL_HEIGHT, intersection);
					renderResult[y][x] = pixelRenderer;
					lastTexturedFloor = y;
					#pragma endregion
				}
			}
		}
		else
		{

		}
		#pragma endregion
	}
	#pragma endregion

	return nullptr;
}

FrameBufferPixel SceneRenderer::renderSurfaceNone()
{
	return FrameBufferPixel(SurfaceTypes::NONE, 1, SurfaceColors::BLACK, true, 1, SurfaceColors::BLACK, 1, 1, SurfaceColors::WHITE, 1);
}

FrameBufferPixel SceneRenderer::renderSurfaceCeiling()
{
	return FrameBufferPixel(SurfaceTypes::CEILING, 1, SurfaceColors::BLUE, true, 1, SurfaceColors::BLACK, 1, 1, SurfaceColors::WHITE, 1);
}

FrameBufferPixel SceneRenderer::renderSurfaceFloor()
{
	return FrameBufferPixel(SurfaceTypes::FLOOR, 1, SurfaceColors::RED, true, 1, SurfaceColors::BLACK, 1, 1, SurfaceColors::WHITE, 1);
}

FrameBufferPixel SceneRenderer::renderSurfaceSky()
{
	return FrameBufferPixel(SurfaceTypes::SKY, 1, SurfaceColors::CYAN, true, 1, SurfaceColors::BLACK, 1, 1, SurfaceColors::WHITE, 1);
}

FrameBufferPixel SceneRenderer::renderSurfacePit()
{
	return FrameBufferPixel(SurfaceTypes::PIT, 1, SurfaceColors::YELLOW, true, 1, SurfaceColors::BLACK, 1, 1, SurfaceColors::WHITE, 1);
}

FrameBufferPixel SceneRenderer::renderSurfaceWall(int y, double ceilingEnd, double perceivedWallHeight, Intersection& intersection)
{
	#pragma Find sample point
	double sampleY = ((double)y - ceilingEnd) / ((double)perceivedWallHeight + 1);
	double sampleX = 0;
	if (intersection.WALL_NORMAL == SurfaceTypes::WALL_NORTH)
		sampleX = -intersection.X;
	else if (intersection.WALL_NORMAL == SurfaceTypes::WALL_NORTH)
		sampleX = intersection.X;
	else if (intersection.WALL_NORMAL == SurfaceTypes::WALL_NORTH)
		sampleX = intersection.Y;
	else
		sampleX = -intersection.Y;
	#pragma endregion

	#pragma region Sample texture from the intersected tile
	Tile renderedTile = this->scene.wallTileFrom(intersection.TILE);
	double texelBrightness = renderedTile.sampleBrightness(sampleX, sampleY);
	SurfaceColors texelColor = renderedTile.sampleColor(sampleY, sampleY);

	const double fogBrightness = 1 - (intersection.DISTANCE / 7);

	return FrameBufferPixel(intersection.WALL_NORMAL,
		texelBrightness, texelColor, true,
		fogBrightness, SurfaceColors::BLACK, 1,
		1, SurfaceColors::WHITE, 1);
}
