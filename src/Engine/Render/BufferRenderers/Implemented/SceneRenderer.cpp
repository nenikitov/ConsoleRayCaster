#include "SceneRenderer.h"
#include <iostream>

SceneRenderer::SceneRenderer(int width, int height, double fontRatio, Scene& scene, Camera& camera)
	: AbstractBufferRenderer(width, height), scene(scene), camera(camera), FONT_RATIO(fontRatio) { }

FrameBufferPixel** SceneRenderer::render()
{
	#pragma region Precalculate and initialize needed values for the whole render
	const double HALF_HEIGHT = this->height / 2.f;
	const double HALF_WIDTH = this->width / 2.f;
	const double HALF_H_FOV = this->camera.getFov() / 2.f;
	const double HALF_V_FOV = atan(tan(HALF_H_FOV) * this->height / (this->width * FONT_RATIO));
	const int WALL_HEIGHT = 1 / tan(HALF_V_FOV) * HALF_HEIGHT;
	const double PERPENDICULAR_LENGTH = HALF_WIDTH / tan(HALF_H_FOV);
	FrameBufferPixel** renderResult = new FrameBufferPixel*[this->height];
	for (int i = 0; i < this->height; i++)
		renderResult[i] = new FrameBufferPixel[this->width];
	#pragma endregion

	for (int x = 0; x < this->width; x++)
	{
		for (int y = 0; y < this->height; y++)
		{
			renderResult[y][x] = FrameBufferPixel(SurfaceTypes::WALL_EAST, y % 2, SurfaceColors::WHITE, true, 1, SurfaceColors::BLACK, 1, 1, SurfaceColors::BLACK, 1);
		}
	}



	/*
	#pragma region Render column by column
	for (int x = 0; x < this->width; x++)
	{
		#pragma region Precalculate and initialize needed values for the current column
		const double RAY_PX_OFFSET = x - HALF_WIDTH;
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
			// Calculate the distance in relation to the camera projection to fix fisheye effect
			const double CORRECTED_DISTANCE = cos(this->camera.getAngle()) * DELTA_X + sin(this->camera.getAngle()) * DELTA_Y;
			// The height of a texel where floor, ceiling and wall should start
			const int PERCEIVED_WALL_HEIGHT = abs(WALL_HEIGHT / CORRECTED_DISTANCE) + 2;
			const double CEILING_END = (this->height - PERCEIVED_WALL_HEIGHT) / 2.f;
			const int FLOOR_START = CEILING_END + PERCEIVED_WALL_HEIGHT;
			// Counter for void renderer
			int lastTexturedFloor = -1;
			#pragma endregion

			#pragma region Render pixel by pixel vertically
			for (int y = 0; y < this->height; y++)
			{
				if (y < CEILING_END)
				{
					#pragma region Ceiling rendering
					FrameBufferPixel pixel = this->renderSurfaceCeiling(x, y, HALF_HEIGHT, HALF_V_FOV, CORRECTED_DISTANCE, WALL_HEIGHT, DELTA_X, DELTA_Y, RAY_H_ANGLE);
					renderResult[y][x] = pixel;
					#pragma endregion
				}
				else if (y > FLOOR_START)
				{
					#pragma region Floor rendering
					FrameBufferPixel pixel = this->renderSurfaceFloor(x, y, HALF_HEIGHT, HALF_V_FOV, CORRECTED_DISTANCE, WALL_HEIGHT, DELTA_X, DELTA_Y, lastTexturedFloor);
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
	*/

	return renderResult;
}

FrameBufferPixel SceneRenderer::renderSurfaceVoid()
{
	return FrameBufferPixel(SurfaceTypes::NONE, 1, SurfaceColors::BLACK, true, 1, SurfaceColors::BLACK, 1, 1, SurfaceColors::WHITE, 1);
}

FrameBufferPixel SceneRenderer::renderSurfaceCeiling(int x, int y, double halfHeight, double halfVFov, double correctedDistance, double wallHeight, double deltaX, double deltaY, double hAngle)
{
	#pragma region Preclacultate and initialize variables
	#pragma region Preclacultate and initialize variables
	double ceilingX;
	double ceilingY;
	double distance;
	double vAngle;
	this->horizontalSurfaceMath(
		true,
		y, halfHeight, halfVFov, wallHeight, correctedDistance, deltaX, deltaY,
		ceilingX, ceilingY, distance, vAngle);

	const int TILE_INDEX = this->scene.ceilingIndexAt(ceilingX, ceilingY);
	const double FOG_TRANSPARENCY = this->calculateFogTransparency(distance);
	#pragma endregion

	if (TILE_INDEX != 0)
	{
		#pragma region Ceiling tile rendering
		Tile renderedTile = this->scene.ceilingTileFrom(TILE_INDEX);

		#pragma region Find sample point
		const double SAMPLE_X = ceilingY;
		const double SAMPLE_Y = -ceilingX;
		#pragma endregion

		#pragma region Sample texture from the rendered tile
		const double SURFACE_BRIGHTNESS = renderedTile.sampleBrightness(SAMPLE_X, SAMPLE_Y);
		const SurfaceColors SURFACE_COLOR = renderedTile.sampleColor(SAMPLE_X, SAMPLE_Y);
		const bool SURFACE_RECEIVE_LIGHTING = renderedTile.sampleReceiveLighting(SAMPLE_X, SAMPLE_Y);
		const double SECTOR_BRIGHTNESS = scene.getSectorBrightness(ceilingX, ceilingY);
        #pragma endregion

		return FrameBufferPixel(
			SurfaceTypes::CEILING, SURFACE_BRIGHTNESS, SURFACE_COLOR, SURFACE_RECEIVE_LIGHTING,
			FOG_TRANSPARENCY, SurfaceColors::BLACK, 1,
			SECTOR_BRIGHTNESS, SurfaceColors::WHITE, 1);
		#pragma endregion
	}
	else
	{
		#pragma region Sky rendering
		Tile skyTile = this->scene.ceilingTileFrom(0);

		#pragma region Find sample point
		const double SAMPLE_X = fmax((this->camera.getAngle() + hAngle) / 6.283184, -1);
		const double SAMPLE_Y = fmax(-vAngle / 1.5708, -1);
		#pragma endregion

		#pragma region Sample texture from the rendered tile
		const double SURFACE_BRIGHTNESS = skyTile.sampleBrightness(SAMPLE_X, SAMPLE_Y);
		SurfaceColors SURFACE_COLOR = skyTile.sampleColor(SAMPLE_X, SAMPLE_Y);
		#pragma endregion

		return FrameBufferPixel(
			SurfaceTypes::SKY, SURFACE_BRIGHTNESS, SURFACE_COLOR, false,
			FOG_TRANSPARENCY, SurfaceColors::BLACK, 1,
			1, SurfaceColors::WHITE, 1);
		#pragma endregion
	}
	#pragma endregion
}

FrameBufferPixel SceneRenderer::renderSurfaceFloor(int x, int y, double halfHeight, double halfVFov, double correctedDistance, double wallHeight, double deltaX, double deltaY, int& lastTexturedFloor)
{
	#pragma region Preclacultate and initialize variables
	double floorX;
	double floorY;
	double distance;
	double vAngle;
	this->horizontalSurfaceMath(
		false,
		y, halfHeight, halfVFov, wallHeight, correctedDistance, deltaX, deltaY,
		floorX, floorY, distance, vAngle);

	const int TILE_INDEX = this->scene.floorIndexAt(floorX, floorY);
	const double FOG_TRANSPARENCY = this->calculateFogTransparency(distance);
	#pragma endregion

	if (TILE_INDEX != 0)
	{
		#pragma region Floor tile rendering
		Tile renderedTile = scene.floorTileFrom(TILE_INDEX);

		#pragma region Find sample point
		const double SAMPLE_X = floorY;
		const double SAMPLE_Y = -floorX;
		#pragma endregion

		#pragma region Sample texture from the rendered tile
		const double SURFACE_BRIGHTNESS = renderedTile.sampleBrightness(SAMPLE_X, SAMPLE_Y);
		const SurfaceColors SURFACE_COLOR = renderedTile.sampleColor(SAMPLE_X, SAMPLE_Y);
		const bool SURFACE_RECEIVE_LIGHTING = renderedTile.sampleReceiveLighting(SAMPLE_X, SAMPLE_Y);
		const double SECTOR_BRIGHTNESS = scene.getSectorBrightness(floorX, floorY);
		#pragma endregion

		lastTexturedFloor = y;

		return FrameBufferPixel(
			SurfaceTypes::FLOOR, SURFACE_BRIGHTNESS, SURFACE_COLOR, SURFACE_RECEIVE_LIGHTING,
			FOG_TRANSPARENCY, SurfaceColors::BLACK, 1,
			SECTOR_BRIGHTNESS, SurfaceColors::WHITE, 1);
		#pragma endregion
	}
	else
	{
		#pragma region Pit rendering
		Tile pitTile = this->scene.floorTileFrom(0);

		#pragma region Find sample point
		const double VOID_RATIO = atan((double)y / this->height) - atan((double)lastTexturedFloor / this->height);
		const double SAMPLE_X = (double)x / this->width * 128;
		const double SAMPLE_Y = fmin(VOID_RATIO / vAngle * halfVFov * 5, 0.99);
		#pragma endregion

		#pragma region Sample texture from the rendered tile
		const double SURFACE_BRIGHTNESS = pitTile.sampleBrightness(SAMPLE_X, SAMPLE_Y);
		SurfaceColors SURFACE_COLOR = pitTile.sampleColor(SAMPLE_X, SAMPLE_Y);
		#pragma endregion

		return FrameBufferPixel(
			SurfaceTypes::PIT, SURFACE_BRIGHTNESS, SURFACE_COLOR, false,
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
	double sectorX = intersection.X;
	double sectorY = intersection.Y;
	if (intersection.WALL_NORMAL == SurfaceTypes::WALL_NORTH)
	{
		sampleX = -intersection.X;
		sectorY -= 0.01;
	}
	else if (intersection.WALL_NORMAL == SurfaceTypes::WALL_SOUTH)
	{
		sampleX = intersection.X;
		sectorY += 0.01;
	}
	else if (intersection.WALL_NORMAL == SurfaceTypes::WALL_WEST)
	{
		sampleX = intersection.Y;
		sectorX -= 0.01;
	}
	else
	{
		sampleX = -intersection.Y;
		sectorX += 0.01;
	}
	#pragma endregion

	#pragma region Sample texture from the rendered tile
	Tile renderedTile = this->scene.wallTileFrom(intersection.TILE);
	const double SURFACE_BRIGHTNESS = renderedTile.sampleBrightness(sampleX, sampleY);
	const SurfaceColors SURFACE_COLOR = renderedTile.sampleColor(sampleX, sampleY);
	const bool SURFACE_RECEIVE_LIGHTING = renderedTile.sampleReceiveLighting(sampleX, sampleY);
	const double SECTOR_BRIGHTNESS = scene.getSectorBrightness(sectorX, sectorY);
	#pragma endregion

	#pragma region Calculate other buffers
	const double FOG_TRANSPARENCY = this->calculateFogTransparency(intersection.DISTANCE);
	#pragma endregion

	return FrameBufferPixel(
		intersection.WALL_NORMAL, SURFACE_BRIGHTNESS, SURFACE_COLOR, SURFACE_RECEIVE_LIGHTING,
		FOG_TRANSPARENCY, SurfaceColors::BLACK, 1,
		SECTOR_BRIGHTNESS, SurfaceColors::WHITE, 1);
}

double SceneRenderer::calculateFogTransparency(double distance)
{
	return 1 - (distance / 3.5);
}

void SceneRenderer::horizontalSurfaceMath(bool invert, int y, double halfHeight, double halfVFov, double wallHeight, double correctedDistance, double deltaX, double deltaY, double& tileX, double& tileY, double& distnace, double& vAngle)
{
	// Vertical angle of the pixel
	vAngle = atan((y - halfHeight) / (halfHeight / tan(halfVFov))) * (invert ? -1 : 1);
	// Ratio of distances between floor texel and wall intersection
	const double PROJECTION_RATIO = (wallHeight / 2 / tan(vAngle)) / correctedDistance / wallHeight;
	// Project the point into world space
	tileX = this->camera.getPosX() + deltaX * PROJECTION_RATIO;
	tileY = this->camera.getPosY() + deltaY * PROJECTION_RATIO;

	distnace = PROJECTION_RATIO * correctedDistance;
}
