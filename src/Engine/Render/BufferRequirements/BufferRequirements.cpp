#include "BufferRequirements.h"

BufferRequirements::BufferRequirements(bool fogBrightness, bool fogColor, bool sectorLightBrightness, bool sectorLightColor)
	: FOG_BRIGHTNESS(fogBrightness), FOG_COLOR(fogColor), SECTOR_LIGHT_BRIGHTNESS(sectorLightBrightness), SECTOR_LIGHT_COLOR(sectorLightColor) { }
