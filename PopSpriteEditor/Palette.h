#pragma once
#include "Editor.h"

namespace Palette
{
	extern void Save(RGB* palette);
	extern bool Load(std::string& file);
	extern bool LoadAlpha(std::string& file);
	extern uint8_t FindClosestColor(RGB rgb);
	extern uint8_t FindColor(RGB rgb, bool closest = false);
	extern uint8_t FindColorAll(RGB rgb, bool closest = false);
	extern bool IndexIsColorKey(uint8_t index);
	extern uint8_t ColorKeys[2];
	extern bool AllColors;
}

extern RGB g_Palette[256];
extern uint8_t g_AlphaTable[256 * 256];