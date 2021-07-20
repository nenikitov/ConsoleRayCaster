#pragma once

#include "CustomBufferTypes/SurfaceColors.h"
#include "CustomBufferTypes/SurfaceTypes.h"

struct FrameBufferPixel
{
	public:
		FrameBufferPixel();
		FrameBufferPixel(
			SurfaceTypes surfaceType, double surfaceBrightness, SurfaceColors surfaceColor, bool surfaceReceiveLighting,
			double fogTransparency, double sectorBrightness);

		// Surface buffers
		SurfaceTypes	surfaceType;
		double			surfaceBrightness;
		SurfaceColors	surfaceColor;
		bool			surfaceReceiveLighting;
		double			fogTransparency;
		double			sectorBrightness;
};
