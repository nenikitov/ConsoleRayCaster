#pragma once

#include "CustomBufferTypes/SurfaceColors.h"
#include "CustomBufferTypes/SurfaceTypes.h"

struct FrameBufferPixel
{
	public:
		FrameBufferPixel();
		FrameBufferPixel(
			SurfaceTypes surfaceType, double surfaceBrightness, SurfaceColors surfaceColor, bool surfaceReceiveLighting,
			double fogBrightness, SurfaceColors fogColor, double fogTransparency,
			double sectorBrightness, SurfaceColors sectorColor, double sectorSaturation);

		// Surface buffers
		SurfaceTypes	surfaceType;
		double			surfaceBrightness;
		SurfaceColors	surfaceColor;
		bool			surfaceReceiveLighting;
		// Fog buffers
		double			fogTransparency;
		SurfaceColors	fogColor;
		double			fogSaturation;
		// Sector lighting buffers
		double			sectorBrightness;
		SurfaceColors	sectorColor;
		double			sectorSaturation;
};
