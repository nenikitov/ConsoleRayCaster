#pragma once

#include <fstream>
#include "../../../../lib/JsonCpp/json/json.h"
#include "../../Render/FrameBuffer/CustomBufferTypes/SurfaceColors.h"
#include "../../Utils/LoadingUtils.h"

class Tile
{
	public:
		Tile(std::string tileName);
		double sampleBrightness(double x, double y);
		bool sampleReceiveLighting(double x, double y);
		SurfaceColors sampleColor(double x, double y);
	private:
		void treatCoords(double x, double y, int& outX, int& outY);

		int textureDimensions;
		double** textureBrightness;
		SurfaceColors** textureColors;
};
