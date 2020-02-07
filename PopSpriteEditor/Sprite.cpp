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
#include "Utility.h"
#include "bitmap_image.hpp"
#include "Palette.h"
#include <filesystem>
#include "Sprite.h"

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
#if 0
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

System::Drawing::Bitmap^ CSprite::getSpriteBitmapHandle(uint16_t index)
{
	uint8_t pal_idx;
	auto sprh = SprBank.Data[index].Sprite.Height;
	auto sprw = SprBank.Data[index].Sprite.Width;

	// Some sprites found inside the bank are corrupt.
	if (sprh == 0 && sprw == 0)
		return gcnew System::Drawing::Bitmap(1, 1);

	auto bmp = gcnew System::Drawing::Bitmap(sprw, sprh);
	MapSprite(index);

	for (uint8_t x = 0; x < sprw; x++)
	{
		for (uint8_t y = 0; y < sprh; y++)
		{
			pal_idx = SprBank.Data[index].Map[x][y];

			if (pal_idx == 0)
				pal_idx = 255;

			auto clr = System::Drawing::Color::FromArgb(
				255,
				g_Palette[pal_idx].R,
				g_Palette[pal_idx].G,
				g_Palette[pal_idx].B
			);

			bmp->SetPixel(x, y, clr);
		}
	}

	return bmp;
}

void CSprite::DumpMemoryToBank(std::string& path)
{
	std::ofstream ofs(path, std::ios::binary | std::ios::trunc);
	if (ofs.is_open())
	{
		ofs.write(m_pBuffer, m_nBufferLength);
		ofs.close();
	}
}

void CSprite::ConvertBitmapToData(bitmap_image sprbmp, std::vector<uint8_t>& vec)
{
	uint8_t bs = 0
		, br = 0;
	uint16_t sprw
		, sprh
		, px = 0
		, br_idx;
	rgb_t rgb_t;
	std::vector<uint8_t> pal;
	bool bClrs = false;

	sprw = sprbmp.width();
	sprh = sprbmp.height();

	for (uint32_t y = 0; y < sprh; y++)
	{
		for (uint32_t x = 0; x < sprw; x++)
		{
			sprbmp.get_pixel(x, y, rgb_t);
			auto idx = Palette::FindColor({ rgb_t.red, rgb_t.green, rgb_t.blue }, true);
			pal.push_back(idx);
		}
	}

	for (const auto& idx : pal)
	{
		if (idx == 255)
		{
			bs++;

			if (bClrs)
			{
				bClrs = false;
				vec[br_idx - 1] = br;
				br = 0;
			}
		}
		else
		{
			if (bs)
			{
				vec.push_back((-bs));
				bs = 0;
			}

			br++;

			if (!bClrs)
			{
				bClrs = true;
				vec.push_back(br);
				br_idx = vec.size();
			}

			vec.push_back(idx);
		}

		px++;

		if (px == sprw)
		{
			vec.push_back(0);
			px = 0;
			bs = 0;

			if (bClrs)
			{
				bClrs = false;
				vec[br_idx - 1] = br;
				br = 0;
			}
		}
	}
}

// Create bank by importing BMP images from the output directory.
void CSprite::ImportToBank(std::string& path)
{
	uint16_t sprw
		, sprh;
	uint32_t sprf = 0
		, spro = 0;
	std::vector<std::pair<uint32_t, bitmap_image>> spri;
	std::vector<uint8_t> conv, pal;
	std::vector<std::vector<uint8_t>> data;
	char szMagic[4] = { 0x50, 0x53, 0x46, 0x42 };

	for (const auto & entry : std::filesystem::directory_iterator((GetCurrentDir() + "output")))
	{
		if (!(entry.is_directory()) && (entry.path().extension() == ".bmp"))
		{
			std::string filename = entry.path().filename().string();
			std::string tmp = filename.substr(0, filename.find(".", 0));

			if (std::all_of(tmp.begin(), tmp.end(), isdigit))
			{
				uint32_t idx = std::stoi(tmp);
				bitmap_image bmp(entry.path().string());

				if (!bmp)
				{
					printf("Problem with bmp index #%i\n", idx);
					// HSPR0-0
					if (idx != 71 && idx != 167 && idx != 2130 && idx != 4484 &&
						idx != 5182 && idx != 5184 && idx != 5186 && idx != 5188 &&
						idx != 5190 && idx != 5192 && idx != 5767 && idx != 6320 &&
						idx != 6876 && idx != 6878 &&
						// hfx0-0
						idx != 1089 && idx != 1449 && idx != 1593 && idx != 1731)
					{
						printf("Failed to open: %s\n", tmp.c_str());
						return;
					}
					else
					{
						bmp.setwidth_height(0, 0);
					}
				}

				spri.push_back(std::make_pair(idx, bmp));
				sprf++;
			}
		}
	}

	std::sort(spri.begin(), spri.end(), [](
		const std::pair<uint32_t, bitmap_image>& fspr, const std::pair<uint32_t, bitmap_image>& sspr)
	{
		return (fspr.first < sspr.first);
	});

	auto it = std::unique(spri.begin(), spri.end(), [](
		const std::pair<uint32_t, bitmap_image>& fspr, const std::pair<uint32_t, bitmap_image>& sspr)
	{
		return fspr.first == sspr.first;
	});

	spri.erase(it, spri.end());

	printf("Imported %i sprites\n", spri.size());

	spro = sizeof(CSprite::BankHeader) + (sizeof(CSprite::TbSprite) * sprf);
	printf("Offset starting at %#04X\n", spro);

	std::ofstream ofs(path, std::ios::binary | std::ios::trunc);
	if (ofs.is_open())
	{
		ofs.write(reinterpret_cast<const char*>(&szMagic), sizeof(char) * 4);
		ofs.write(reinterpret_cast<const char*>(&sprf), sizeof(uint32_t));

		for (uint32_t i = 0; i < sprf; i++)
		{
			sprw = spri[i].second.width();
			sprh = spri[i].second.height();
			ConvertBitmapToData(spri[i].second, conv);

			ofs.write(reinterpret_cast<const char*>(&sprw), sizeof(uint16_t));
			ofs.write(reinterpret_cast<const char*>(&sprh), sizeof(uint16_t));
			ofs.write(reinterpret_cast<const char*>(&spro), sizeof(uint32_t));

			spro = spro + conv.size();
			data.push_back(conv);
			conv.clear();
		}

		for (uint32_t i = 0; i < sprf; i++)
		{
			for (const auto& b : data[i])
			{
				ofs.write(reinterpret_cast<const char*>(&b), sizeof(uint8_t));
			}
		}

		ofs.close();
	}
}