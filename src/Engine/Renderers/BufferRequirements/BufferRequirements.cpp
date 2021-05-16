#include "BufferRequirements.h"

BufferRequirements::BufferRequirements(bool fogBrightness, bool fogColor, bool lightBrightness, bool lightColor)
	: FOG_BRIGHTNESS(fogBrightness), FOG_COLOR(fogColor), LIGHT_BRIGHTNESS(lightBrightness), LIGHT_COLOR(lightColor) { }
