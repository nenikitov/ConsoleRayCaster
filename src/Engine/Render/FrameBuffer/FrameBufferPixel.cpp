#include "FrameBufferPixel.h"

FrameBufferPixel::FrameBufferPixel()
{
	this->surfaceType = SurfaceTypes::NONE;
	this->surfaceBrightness = 0;
	this->surfaceColor = SurfaceColors::BLACK;
	this->surfaceReceiveLighting = false;

	this->fogTransparency = 0;
	this->sectorBrightness = 0;
}

FrameBufferPixel::FrameBufferPixel(
	SurfaceTypes surfaceType, double surfaceBrightness, SurfaceColors surfaceColor, bool surfaceReceiveLighting,
	double fogTransparency, double sectorBrightness)
{
	this->surfaceType = surfaceType;
	this->surfaceBrightness = surfaceBrightness;
	this->surfaceColor = surfaceColor;
	this->surfaceReceiveLighting = surfaceReceiveLighting;

	this->fogTransparency = fogTransparency;
	this->sectorBrightness = sectorBrightness;
}
