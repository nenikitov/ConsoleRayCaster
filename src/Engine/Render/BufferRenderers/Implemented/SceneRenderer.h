#pragma once

#include "../Abstract/AbstractBufferRenderer.h"
#include "../../../Scene/Scene/Scene.h"
#include "../../../Scene/GameObject/Implemented/Camera/Camera.h"

class SceneRenderer : public AbstractBufferRenderer
{
	public:
		SceneRenderer(int width, int height, Scene& scene, Camera& camera);
		FrameBuffer** render() override;
	private:
		const Scene& SCENE;
		const Camera& CAMERA;
};
