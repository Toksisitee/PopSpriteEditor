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

#include <vector>
#include <cstdint>
#include <fstream>
#include "Sprite.h"
#include "Utility.h"
#include "bitmap_image.hpp"
#include "Palette.h"

bool CSprite::LoadBank(const std::string& file)
{
	printf("Opening sprite bank\n");

	if (SprBank.Data.size() > 0)
		this->Clear();

	std::ifstream ifs(file, std::ios::binary | std::ios::ate);
	if (ifs.is_open())
	{
		m_nBufferLength = static_cast<uint32_t>(ifs.tellg());
		m_pBuffer = new char[m_nBufferLength];
		char* buffer = m_pBuffer;
		ifs.seekg(std::ios::beg);
		ifs.read(m_pBuffer, m_nBufferLength);
		ifs.close();

		SprBank.Header = *(reinterpret_cast<CSprite::BankHeader*>(buffer));
		buffer += sizeof(CSprite::BankHeader);

		if (memcmp(SprBank.Header.Magic, "PSFB", 4) != 0)
		{
			printf("Wrong magic number %s. Not a valid sprite bank?\n", SprBank.Header.Magic);
			this->Clear();
			return false;
		}

		printf("Found %i sprite frames.\n", SprBank.Header.Frames);

		for (uint32_t i = 0; i < SprBank.Header.Frames; i++)
		{
			/*
			sprData.Sprite->Width = *(reinterpret_cast<uint16_t*>(buffer));
			buffer += sizeof(uint16_t);
			sprData.Sprite->Height = *(reinterpret_cast<uint16_t*>(buffer));
			buffer += sizeof(uint16_t);
			sprData.Offset = *(reinterpret_cast<uint32_t*>(buffer));
			buffer += sizeof(uint32_t);
			sprData.Sprite->Data = reinterpret_cast<int8_t*>(sprData.Offset);
			sprFile.Data.push_back(sprData);
			*/

			SprBank.Data.push_back({ *(reinterpret_cast<CSprite::TbSprite*>(buffer)) });
			SprBank.Data.back().Data = reinterpret_cast<int8_t*>(m_pBuffer + SprBank.Data.back().Sprite.Offset);
			buffer += sizeof(CSprite::TbSprite);
#if 1
			printf("#%i Height: %i, Width: %i, Offsets: (H)%06X && (D)%06X\n", i, SprBank.Data.back().Sprite.Height, SprBank.Data.back().Sprite.Width, ((1 + i) * sizeof(CSprite::BankHeader)), SprBank.Data.back().Sprite.Offset);
#endif
		}
		return true;
	}
	
	printf("Could not open sprite bank: %s.\n", file.c_str());

	if (!FileExists(file))
	{
		printf("File does not exist\n");
	}

	return false;
}

void CSprite::MapSprite(uint16_t index)
{
	int8_t b;

	if (SprBank.Data[index].Map.size() < 1)
	{
		SprBank.Data[index].Map.resize(SprBank.Data[index].Sprite.Width, std::vector<int32_t>(SprBank.Data[index].Sprite.Height, 0));

		for (uint32_t x = 0, y = 0, p = 0; y < SprBank.Data[index].Sprite.Height; y++, x = 0)
		{
			while (true)
			{
				b = SprBank.Data[index].Data[p];
				p++;

				if (b == 0)
				{
					SprBank.Data[index].Raw.push_back({ static_cast<uint8_t>(b), REND });
					break;
				}

				if (b < 0)
				{
					SprBank.Data[index].Raw.push_back({ static_cast<uint8_t>(b), RSKIP });
					x += -b;
				}
				else if (b > 0)
				{
					SprBank.Data[index].Raw.push_back({ static_cast<uint8_t>(b), RREAD });

					for (uint32_t i = 0, n = b; i < n; i++)
					{
						if (x < SprBank.Data[index].Sprite.Width && y < SprBank.Data[index].Sprite.Height)
						{
							b = SprBank.Data[index].Data[p];
							SprBank.Data[index].Map[x][y] = b;
							SprBank.Data[index].Raw.push_back({ static_cast<uint8_t>(b), RPAL });
							p++;
							x++;
						}

					}
				}
			}
		}
	}
}

void CSprite::SaveSprite(uint16_t index)
{
	printf("Saving Sprite: %i\n", index);

	uint8_t pal_idx;
	bitmap_image bmp(SprBank.Data[index].Sprite.Width, SprBank.Data[index].Sprite.Height);
	bmp.clear();

	MapSprite(index);

	for (uint8_t x = 0; x < SprBank.Data[index].Sprite.Width; x++)
	{
		for (uint8_t y = 0; y < SprBank.Data[index].Sprite.Height; y++)
		{
			pal_idx = SprBank.Data[index].Map[x][y];

			if (pal_idx == 0)
				pal_idx = 255;

			bmp.set_pixel(x, y, g_Palette[pal_idx].R, g_Palette[pal_idx].G, g_Palette[pal_idx].B);
		}
	}

	bmp.save_image(GetCurrentDir() + "//output//" + std::to_string(index) + ".bmp");
}