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
	FrameBufferPixel** frameBuffer = new FrameBufferPixel*[this->height];
	for (int i = 0; i < this->height; i++)
		frameBuffer[i] = (FrameBufferPixel*) malloc(this->width * sizeof(FrameBufferPixel));
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
			const int WALL_START = abs(WALL_HEIGHT / CORRECTED_DISTANCE);
			const double CEILING_START = (this->height - WALL_START) / 2.f;
			const int FLOOR_START = CEILING_START + this->height;
			#pragma endregion


		}
		else
		{

		}
		#pragma endregion
	}
	#pragma endregion

	return nullptr;
}
