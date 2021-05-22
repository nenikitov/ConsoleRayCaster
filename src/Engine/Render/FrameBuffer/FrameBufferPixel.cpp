#include "FrameBufferPixel.h"

FrameBufferPixel::FrameBufferPixel(
	SurfaceTypes surfaceType, double surfaceBrightness, SurfaceColors surfaceColor, bool surfaceReceiveLighting,
	double fogTransparency, SurfaceColors fogColor, double fogSaturation,
	double sectorBrightness, SurfaceColors sectorColor, double sectorSaturation)
{
	this->surfaceType = surfaceType;
	this->surfaceBrightness = surfaceBrightness;
	this->surfaceColor = surfaceColor;
	this->surfaceReceiveLighting = surfaceReceiveLighting;
	this->fogTransparency = fogTransparency;
	this->fogColor = fogColor;
	this->fogSaturation = fogSaturation;
	this->sectorBrightness = sectorBrightness;
	this->sectorColor = sectorColor;
	this->sectorSaturation = sectorSaturation;
}
