#pragma once

struct BufferRequirements
{
	public:
		BufferRequirements(bool fogBrightness, bool fogColor, bool sectorLightBrightness, bool sectorLightColor);

		const bool FOG_BRIGHTNESS;
		const bool FOG_COLOR;
		const bool SECTOR_LIGHT_BRIGHTNESS;
		const bool SECTOR_LIGHT_COLOR;
};
