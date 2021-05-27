#pragma once

#include <fstream>
#include "../../../../lib/JsonCpp/json/json.h"
#include "../../Render/FrameBuffer/CustomBufferTypes/SurfaceColors.h"

class Tile
{
	public:
		Tile(std::string tileName);
		double sampleBrightness(double x, double y);
		SurfaceColors sampleColor(double x, double y);
	private:
		void treatCoords(double x, double y, int& outX, int& outY);

		unsigned short textureDimensions;
		double** textureBrightness;
		SurfaceColors** textureColors;
};
