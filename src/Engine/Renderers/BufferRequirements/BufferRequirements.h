#pragma once

struct BufferRequirements
{
public:
	BufferRequirements(bool fogBrightness, bool fogColor, bool lightBrightness, bool lightColor);

	const bool FOG_BRIGHTNESS;
	const bool FOG_COLOR;
	const bool LIGHT_BRIGHTNESS;
	const bool LIGHT_COLOR;
};
