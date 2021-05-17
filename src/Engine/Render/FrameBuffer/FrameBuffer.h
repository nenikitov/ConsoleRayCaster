#pragma once

#include "CustomBufferTypes/SurfaceColors.h"
#include "CustomBufferTypes/SurfaceTypes.h"

struct FrameBuffer
{
	public:
		FrameBuffer(
			SurfaceTypes surfaceType, SurfaceColors surfaceColor, bool surfaceReceiveLighting, 
			double fogBrightness, SurfaceColors fogColor, double fogSaturation,
			double sectorBrightness, SurfaceColors sectorColor, double sectorSaturation);

		// Surface buffers
		const SurfaceTypes	SURFACE_TYPE;
		const SurfaceColors	SURFACE_COLOR;
		const bool			SURFACE_RECEIVE_LIGHTING;
		// Fog buffers
		const double		FOG_BRIGTNESS;
		const SurfaceColors	FOG_COLOR;
		const double		FOG_SATURAION;
		// Sector lighting buffers
		const double		SECTOR_BRIGHTNESS;
		const SurfaceColors	SECTOR_COLOR;
		const double		SECTOR_SATURAION;
};
