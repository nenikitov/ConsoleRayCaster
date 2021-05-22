#pragma once

#include "../Abstract/AbstractBufferRenderer.h"
#include "../../../Scene/Scene/Scene.h"
#include "../../../Scene/GameObject/Implemented/Camera/Camera.h"
#include "../../../RayCaster/Intersection/Intersection.h"
#include "../../../RayCaster/RayCaster/RayCaster.h"

class SceneRenderer : public AbstractBufferRenderer
{
	public:
		SceneRenderer(int width, int height, Scene& scene, Camera& camera);
		FrameBufferPixel** render() override;
	private:
		Scene& scene;
		Camera& camera;
};
