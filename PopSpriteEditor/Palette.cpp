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