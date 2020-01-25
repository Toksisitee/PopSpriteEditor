#pragma once

struct RGB
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
};

namespace Palette
{
	extern void Save(RGB* Palette);
	extern void Load(std::string& file);
	extern uint8_t FindClosestColor(RGB rgb);
	extern uint8_t FindColor(RGB rgb, bool closest = false);
}

extern RGB g_Palette[256];