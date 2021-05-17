#pragma once

#include "CustomBufferTypes/SurfaceColors.h"
#include "CustomBufferTypes/SurfaceTypes.h"
#include "CustomBufferTypes/SurfaceLightResponses.h"

struct VisualizerBuffers
{
	// Surface buffers
	const SurfaceTypes          SURFACE_TYPE;
	const SurfaceColors         SURFACE_COLOR;
	const SurfaceLightResponses SURFACE_LIGHT_RESPONSE;
	// Fog buffers
	const double                FOG_BRIGTNESS;
	const SurfaceColors         FOG_COLOR;
	const double                FOG_SATURAION;
	// Level lighting buffers
	const double                SECTOR_BRIGHTNESS;
	const SurfaceColors         SECTOR_COLOR;
	const double                SECTOR_SATURAION;
};
