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
		renderResult[i] = new FrameBufferPixel[this->width];
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
					FrameBufferPixel pixel = this->renderSurfaceCeiling(x, y, HALF_HEIGHT, HALF_V_FOV, CORRECTED_DISTANCE, PERCEIVED_WALL_HEIGHT, DELTA_X, DELTA_Y, RAY_H_ANGLE);
					renderResult[y][x] = pixel;
					#pragma endregion
				}
				else if (y > FLOOR_START)
				{
					#pragma region Floor rendering
					FrameBufferPixel pixel = this->renderSurfaceFloor(x, y, HALF_HEIGHT, HALF_V_FOV, CORRECTED_DISTANCE, PERCEIVED_WALL_HEIGHT, DELTA_X, DELTA_Y, lastTexturedFloor);
					renderResult[y][x] = pixel;
					#pragma endregion
				}
				else
				{
					#pragma region Wall Rendering
					FrameBufferPixel pixel = this->renderSurfaceWall(y, CEILING_END, PERCEIVED_WALL_HEIGHT, intersection);
					renderResult[y][x] = pixel;
					lastTexturedFloor = y;
					#pragma endregion
				}
			}
			#pragma endregion
		}
		else
		{
			for (int y = 0; y < this->height; y++)
			{
				FrameBufferPixel pixel = this->renderSurfaceVoid();
				renderResult[y][x] = pixel;
			}
		}
		#pragma endregion
	}
	#pragma endregion
	
	return renderResult;
}

FrameBufferPixel SceneRenderer::renderSurfaceVoid()
{
	return FrameBufferPixel(SurfaceTypes::NONE, 1, SurfaceColors::BLACK, true, 1, SurfaceColors::BLACK, 1, 1, SurfaceColors::WHITE, 1);
}

FrameBufferPixel SceneRenderer::renderSurfaceCeiling(int x, int y, double halfHeight, double halfVFov, double correctedDistance, double perceivedWallHeight, double deltaX, double deltaY, double hAngle)
{
	#pragma region Preclacultate and initialize variables
	// Vertical angle of the pixel
	const double V_ANGLE = (y - halfHeight) / (double)this->width * halfVFov;
	// Ratio of distances between floor texel and wall intersection
	const double PROJECTION_RATIO = -(perceivedWallHeight / 2 / tan(V_ANGLE)) / correctedDistance / this->width;
	// Project the point into world space
	const double CEILING_X = this->camera.getPosX() + deltaX * PROJECTION_RATIO;
	const double CEILING_Y = this->camera.getPosY() + deltaY * PROJECTION_RATIO;
	const int TILE_INDEX = this->scene.ceilingIndexAt(CEILING_X, CEILING_Y);
	#pragma endregion

	if (TILE_INDEX != 0)
	{
		#pragma region Ceiling tile rendering
		Tile renderedTile = scene.ceilingTileFrom(TILE_INDEX);

		#pragma region Find sample point
		const double SAMPLE_X = CEILING_Y;
		const double SAMPLE_Y = -CEILING_X;
		#pragma endregion

		#pragma region Sample texture from the rendered tile
		const double SURFACE_BRIGHTNESS = renderedTile.sampleBrightness(SAMPLE_X, SAMPLE_Y);
		const SurfaceColors SURFACE_COLOR = renderedTile.sampleColor(SAMPLE_Y, SAMPLE_Y);
#		pragma endregion

		#pragma region Calculate other buffers
		const double DISTANCE = halfHeight / tan(V_ANGLE) / this->height;
		const double FOG_TRANSPARENCY = 1 - (DISTANCE / 49);
		#pragma endregion

		return FrameBufferPixel(SurfaceTypes::CEILING,
			SURFACE_BRIGHTNESS, SURFACE_COLOR, true,
			FOG_TRANSPARENCY, SurfaceColors::BLACK, 1,
			1, SurfaceColors::WHITE, 1);
		#pragma endregion
	}
	else
	{
		#pragma region Sky rendering
		Tile voidTile = this->scene.ceilingTileFrom(0);

		#pragma region Find sample point
		const double SAMPLE_X = fmax((this->camera.getAngle() + hAngle) / 3.141592 / 2, -1);
		const double SAMPLE_Y = fmin(-V_ANGLE / 0.5708 - 0.5, -0.01);
		#pragma endregion

		#pragma region Sample texture from the rendered tile
		const double SURFACE_BRIGHTNESS = voidTile.sampleBrightness(SAMPLE_X, SAMPLE_Y);
		SurfaceColors SURFACE_COLOR = voidTile.sampleColor(SAMPLE_Y, SAMPLE_Y);
		#pragma endregion

		return FrameBufferPixel(SurfaceTypes::SKY,
			SURFACE_BRIGHTNESS, SURFACE_COLOR, true,
			1, SurfaceColors::BLACK, 1,
			1, SurfaceColors::WHITE, 1);
		#pragma endregion
	}
	#pragma endregion
}

FrameBufferPixel SceneRenderer::renderSurfaceFloor(int x, int y, double halfHeight, double halfVFov, double correctedDistance, double perceivedWallHeight, double deltaX, double deltaY, int& lastTexturedFloor)
{
	#pragma region Preclacultate and initialize variables
	// Vertical angle of the pixel
	const double V_ANGLE = (y - halfHeight) / (double)this->width * halfVFov;
	// Ratio of distances between floor texel and wall intersection
	const double PROJECTION_RATIO = (perceivedWallHeight / 2 / tan(V_ANGLE)) / correctedDistance / this->width;
	// Project the point into world space
	const double FLOOR_X = this->camera.getPosX() + deltaX * PROJECTION_RATIO;
	const double FLOOR_Y = this->camera.getPosY() + deltaY * PROJECTION_RATIO;
	const int TILE_INDEX = this->scene.floorIndexAt(FLOOR_X, FLOOR_Y);
	#pragma endregion

	if (TILE_INDEX != 0)
	{
		#pragma region Floor tile rendering
		Tile renderedTile = scene.floorTileFrom(TILE_INDEX);

		#pragma region Find sample point
		const double SAMPLE_X = FLOOR_Y;
		const double SAMPLE_Y = -FLOOR_X;
		#pragma endregion

		#pragma region Sample texture from the rendered tile
		const double SURFACE_BRIGHTNESS = renderedTile.sampleBrightness(SAMPLE_X, SAMPLE_Y);
		const SurfaceColors SURFACE_COLOR = renderedTile.sampleColor(SAMPLE_Y, SAMPLE_Y);
		#pragma endregion

		#pragma region Calculate other buffers
		const double DISTANCE = halfHeight / tan(V_ANGLE) / this->height;
		const double FOG_TRANSPARENCY = 1 - (DISTANCE / 49);
		lastTexturedFloor = y;
		#pragma endregion

		return FrameBufferPixel(SurfaceTypes::FLOOR,
			SURFACE_BRIGHTNESS, SURFACE_COLOR, true,
			FOG_TRANSPARENCY, SurfaceColors::BLACK, 1,
			1, SurfaceColors::WHITE, 1);
		#pragma endregion
	}
	else
	{
		#pragma region Pit rendering
		Tile voidTile = this->scene.floorTileFrom(0);

		#pragma region Find sample point
		const double VOID_RATIO = ((double)y - lastTexturedFloor) / V_ANGLE / this->height;
		const double SAMPLE_X = (double)x / this->width * 64;
		const double SAMPLE_Y = fmin(VOID_RATIO * halfVFov, 0.99);
		#pragma endregion

		#pragma region Sample texture from the rendered tile
		const double SURFACE_BRIGHTNESS = voidTile.sampleBrightness(SAMPLE_X, SAMPLE_Y);
		SurfaceColors SURFACE_COLOR = voidTile.sampleColor(SAMPLE_Y, SAMPLE_Y);
		#pragma endregion

		#pragma region Calculate other buffers
		const double DISTANCE = halfHeight / tan(V_ANGLE) / this->height;
		const double FOG_TRANSPARENCY = 1 - (DISTANCE / 49);
		#pragma endregion

		return FrameBufferPixel(SurfaceTypes::PIT,
			SURFACE_BRIGHTNESS, SURFACE_COLOR, true,
			FOG_TRANSPARENCY, SurfaceColors::BLACK, 1,
			1, SurfaceColors::WHITE, 1);
		#pragma endregion
	}
	#pragma endregion
}

FrameBufferPixel SceneRenderer::renderSurfaceWall(int y, double ceilingEnd, double perceivedWallHeight, Intersection& intersection)
{
	#pragma region Find sample point
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

	#pragma region Sample texture from the rendered tile
	Tile renderedTile = this->scene.wallTileFrom(intersection.TILE);
	double texelBrightness = renderedTile.sampleBrightness(sampleX, sampleY);
	SurfaceColors texelColor = renderedTile.sampleColor(sampleY, sampleY);
	#pragma endregion

	#pragma region Calculate other buffers
	const double FOG_TRANSPARENCY = 1 - (intersection.DISTANCE / 7);
	#pragma endregion

	return FrameBufferPixel(intersection.WALL_NORMAL,
		texelBrightness, texelColor, true,
		FOG_TRANSPARENCY, SurfaceColors::BLACK, 1,
		1, SurfaceColors::WHITE, 1);
}
