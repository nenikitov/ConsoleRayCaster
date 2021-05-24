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

		FrameBufferPixel renderSurfaceVoid();
		FrameBufferPixel renderSurfaceCeiling(int x, int y, double halfHeight, double halfVFov, double correctedDistance, double perceivedWallHeight, double deltaX, double deltaY, double hAngle);
		FrameBufferPixel renderSurfaceFloor(int x, int y, double halfHeight, double halfVFov, double correctedDistance, double wallHeight, double deltaX, double deltaY, int& lastTexturedFloor);
		FrameBufferPixel renderSurfaceWall(int y, double ceilingEnd, double perceivedWallHeight, Intersection& intersection);
};
