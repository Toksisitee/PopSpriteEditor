/*
	Copyright © 2020 Toksisitee <meypcm@gmail.com>

	PopSpriteEditor is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	PopSpriteEditor is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include "bitmap_image.hpp"
#include "Utility.h"
#include "Palette.h"

RGB g_Palette[256];

void Palette::Save(RGB* Palette)
{
	bitmap_image pal(16, 16);
	pal.clear();

	int index = 0;
	for (uint32_t y = 0; y < pal.height(); y++)
	{
		for (uint32_t x = 0; x < pal.width(); x++)
		{
			pal.set_pixel(x, y, Palette[index].R, Palette[index].G, Palette[index].B);
			index++;
		}
	}

	pal.save_image(GetCurrentDir() + "//output//pal.bmp");
}

void Palette::Load(std::string& file)
{
	char pad;
	std::ifstream ifs(file, std::ios::binary);

	if (ifs.is_open())
	{
		ifs.seekg(0);

		for (uint32_t i = 0; i < 256; i++)
		{
			ifs.read(reinterpret_cast<char*>(&g_Palette[i].R), sizeof(uint8_t));
			ifs.read(reinterpret_cast<char*>(&g_Palette[i].G), sizeof(uint8_t));
			ifs.read(reinterpret_cast<char*>(&g_Palette[i].B), sizeof(uint8_t));
			ifs.read(&pad, sizeof(uint8_t));
		}
	}

	ifs.close();
}

uint8_t Palette::FindClosestColor(RGB rgb)
{
	uint8_t index = 255;
	double closestDist = DBL_MAX;

	for (int i = 128; i < 256; i++)
	{
		auto deltaE = sqrt(
			pow(rgb.R - g_Palette[i].R, 2) +
			pow(rgb.G - g_Palette[i].G, 2) +
			pow(rgb.B - g_Palette[i].B, 2));

		if (deltaE < closestDist)
		{
			index = i;
			closestDist = deltaE;
		}
	}

	return index;
}

uint8_t Palette::FindColor(RGB rgb, bool closest)
{
	for (int i = 128; i < 256; i++)
	{
		if (rgb.R == g_Palette[i].R &&
			rgb.G == g_Palette[i].G &&
			rgb.B == g_Palette[i].B)
		{
			return (i);
		}
	}

	// Just a fallback
	if (closest)
		return Palette::FindClosestColor(rgb);

	return 255;
}