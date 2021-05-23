#pragma once

#include "AbstractPlayer.h"

class FPSPlayer : public AbstractPlayer
{
	public:
		FPSPlayer(Scene& scene, double fov);
		virtual void tick(double deltaTime) override;
};
