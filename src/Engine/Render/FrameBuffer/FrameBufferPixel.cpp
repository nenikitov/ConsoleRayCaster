#include "FrameBufferPixel.h"

FrameBufferPixel::FrameBufferPixel(
	SurfaceTypes surfaceType, double surfaceBrightness, SurfaceColors surfaceColor, bool surfaceReceiveLighting,
	double fogBrightness, SurfaceColors fogColor, double fogSaturation,
	double sectorBrightness, SurfaceColors sectorColor, double sectorSaturation)
		: SURFACE_TYPE(surfaceType),
		SURFACE_BRIGHTNESS(surfaceBrightness),
		SURFACE_COLOR(surfaceColor),
		SURFACE_RECEIVE_LIGHTING(surfaceReceiveLighting),
		FOG_BRIGTNESS(fogBrightness),
		FOG_COLOR(fogColor),
		FOG_SATURAION(fogSaturation),
		SECTOR_BRIGHTNESS(sectorBrightness),
		SECTOR_COLOR(sectorColor),
		SECTOR_SATURAION(sectorSaturation) { }
