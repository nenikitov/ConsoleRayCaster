#pragma once

#include "../Abstract/AbstractBufferRenderer.h"
#include "../../../Scene/Scene/Scene.h"

class SceneRenderer : public AbstractBufferRenderer
{
	public:
		SceneRenderer(Scene& scene);
		FrameBuffer** render() override;
	private:
		const Scene& SCENE;
};
