#include "SceneRenderer.h"

SceneRenderer::SceneRenderer(int width, int height, Scene& scene, Camera& camera)
	: AbstractBufferRenderer(width, height), scene(scene), camera(camera) { }

FrameBuffer** SceneRenderer::render()
{
	#pragma region Precalculate and initialize needed values for the whole render
	const double HALF_HEIGHT = this->height / 2.f;
	const double HALF_H_FOV = this->camera.getFov() / 2.f;
	const double HALF_V_FOV = HALF_H_FOV / (double)this->width * (double)this->height / 2.f;
	const double PERPENDICULAR_LENGTH = width / 2.f / tan(HALF_H_FOV);
	FrameBuffer** frameBuffer = new FrameBuffer*[this->height];
	#pragma endregion

	#pragma region Render column by column
	for (int x = 0; x < this->width; x++)
	{
		#pragma region Precalculate and initialize needed values for the current column
		const double RAY_PX_OFFSET = (double)x - this->width / 2.f;
		const double RAY_H_ANGLE = atan(RAY_PX_OFFSET / PERPENDICULAR_LENGTH);
		#pragma endregion

		#pragma region Find intersection
		Intersection intersection = RayCaster::trace(this->scene, camera.getPosX(), camera.getPosY(), camera.getAngle() + RAY_H_ANGLE);
		#pragma endregion

		#pragma Render from intersection
		if (intersection.VALID)
		{

		}
		else
		{

		}
		#pragma endregion
	}
	#pragma endregion

	return nullptr;
}
