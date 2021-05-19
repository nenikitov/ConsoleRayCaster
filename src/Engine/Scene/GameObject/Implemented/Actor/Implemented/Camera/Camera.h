#pragma once

#include "../../Abstract/AbstractActor.h"

class Camera : public AbstractActor
{
	virtual void act(double deltaTime) override;
};
