#pragma once

#include "../../Abstract/AbstractGameObject.h"

class AbstractPlayer : public AbstractGameObject
{
	virtual void tick(double deltaSeconds) = 0;
};
