#include "FrameBufferPixel.h"

FrameBufferPixel::FrameBufferPixel()
{
	this->surfaceType = SurfaceTypes::NONE;
	this->surfaceBrightness = 0;
	this->surfaceColor = SurfaceColors::BLACK;
	this->surfaceReceiveLighting = false;

	this->fogTransparency = 0;
	this->fogColor = SurfaceColors::BLACK;
	this->fogSaturation = 0;

	this->sectorBrightness = 0;
	this->sectorColor = SurfaceColors::BLACK;
	this->sectorSaturation = 0;
}

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
