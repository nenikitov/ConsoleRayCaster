#include "SceneRenderer.h"

SceneRenderer::SceneRenderer(int width, int height, Scene& scene, Camera& camera)
	: AbstractBufferRenderer(width, height), SCENE(scene), CAMERA(camera) { }

FrameBuffer** SceneRenderer::render()
{
	return nullptr;
}
