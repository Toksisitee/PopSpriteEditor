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

#include <cstdint>
#include <fstream>
#include "Utility.h"
#include "Palette.h"
#include <filesystem>
#include <algorithm>
#include "Sprite.h"
#include "Editor.h"

CSprite g_Sprite;

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

		if (SprBank.Header.Frames == 0)
		{
			printf("Couldn't find any sprite frames..\n");
			this->Clear();
			return false;
		}

		printf("Found %i sprite frames.\n", SprBank.Header.Frames);

		for (uint32_t i = 0; i < SprBank.Header.Frames; i++)
		{
			SprBank.Data.push_back({ *(reinterpret_cast<CSprite::TbSprite*>(buffer)) });
			SprBank.Data.back().Data = reinterpret_cast<int8_t*>(m_pBuffer + SprBank.Data.back().Sprite.Offset);
			buffer += sizeof(CSprite::TbSprite);
#if 0
			printf("#%i Height: %i, Width: %i, Offsets: (H)%06X && (D)%06X\n", i, SprBank.Data.back().Sprite.Height, SprBank.Data.back().Sprite.Width, ((1 + i) * sizeof(CSprite::BankHeader)), SprBank.Data.back().Sprite.Offset);
#endif
		}
		printf("Opened sprite bank file.\n");
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
					for (; x < SprBank.Data[index].Sprite.Width; x++)
						SprBank.Data[index].Map[x][y] = Palette::ColorKeys[0];
					break;
				}

				if (b < 0)
				{
					SprBank.Data[index].Raw.push_back({ static_cast<uint8_t>(b), RSKIP });
					for (uint32_t i = 0; i <= (-b); i++)
						SprBank.Data[index].Map[x + i][y] = Palette::ColorKeys[0];
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

void CSprite::ExportSprite(uint16_t index)
{
	uint8_t pal_idx;
	BMP bmp;
	uint16_t min = 1;
	bmp.SetSize(std::max(min, SprBank.Data[index].Sprite.Width), std::max(min, SprBank.Data[index].Sprite.Height));
	bmp.SetBitDepth(24);

	MapSprite(index);
	
	for (uint16_t x = 0; x < SprBank.Data[index].Sprite.Width; x++)
	{
		for (uint16_t y = 0; y < SprBank.Data[index].Sprite.Height; y++)
		{
			pal_idx = SprBank.Data[index].Map[x][y];

			if (Palette::IndexIsColorKey(pal_idx))
				pal_idx = Palette::ColorKeys[0];

			bmp.SetPixel(x, y, { g_Palette[pal_idx].B, g_Palette[pal_idx].G, g_Palette[pal_idx].R, 0 });
		}
	}

	bmp.WriteToFile((GetCurrentDir() + "//output//" + std::to_string(index) + ".bmp").c_str());
}

void CSprite::ExportSprites()
{
	if (SprBank.Header.Frames > 0)
	{
		printf("Exporting sprites, please wait..\n");
		for (uint32_t i = 0; i < g_Sprite.SprBank.Header.Frames; i++)
		{
			g_Sprite.ExportSprite(i);
		}
		printf("Done\n");
	}
	else
		printf("Load a valid sprite bank to export sprites.\n");
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

	for (uint16_t x = 0; x < sprw; x++)
	{
		for (uint16_t y = 0; y < sprh; y++)
		{
			pal_idx = SprBank.Data[index].Map[x][y];

			if (Palette::IndexIsColorKey(pal_idx))
				pal_idx = Palette::ColorKeys[0];

			if (IsAlphaSprite(index))
				if (pal_idx != 255)
					pal_idx = g_AlphaTable[pal_idx * 256];

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

void CSprite::ConvertBitmapToData(BMP sprbmp, std::vector<uint8_t>& vec, int32_t index, uint32_t maxIndex)
{
	uint8_t bs = 0
		, br = 0,
		pal_idx;
	uint16_t sprw
		, sprh
		, px = 0
		, br_idx;
	RGBApixel rgb;
	std::vector<uint8_t> pal;
	bool bClrs = false;
	sprw = sprbmp.TellWidth();
	sprh = sprbmp.TellHeight();

	for (uint32_t y = 0; y < sprh; y++)
	{
		for (uint32_t x = 0; x < sprw; x++)
		{
			rgb = sprbmp.GetPixel(x, y);

			if (IsAlphaSprite(index))
				pal_idx = Palette::FindColorAll({ rgb.Red, rgb.Green, rgb.Blue }, true);
			else
				pal_idx = Palette::FindColor({ rgb.Red, rgb.Green, rgb.Blue }, true);

			pal.push_back(pal_idx);
		}
	}

	for (const auto& idx : pal)
	{
		if (Palette::IndexIsColorKey(idx))
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
		, spro = 0
		, sprs = 0;
	std::vector<std::pair<uint32_t, std::shared_ptr<BMP>>> spri;
	std::vector<uint8_t> conv, pal;
	std::vector<std::vector<uint8_t>> data;
	char szMagic[4] = { 0x50, 0x53, 0x46, 0x42 };
	bool isHFX = m_IsHFX;

	for (const auto & entry : std::filesystem::directory_iterator((GetCurrentDir() + "output")))
	{
		if (!(entry.is_directory()) && (entry.path().extension() == ".bmp"))
		{
			std::string filename = entry.path().filename().string();
			std::string tmp = filename.substr(0, filename.find(".", 0));

			if (std::all_of(tmp.begin(), tmp.end(), isdigit))
			{
				uint32_t idx = std::stoi(tmp);
				auto bmp = std::make_shared<BMP>();
				if (!bmp->ReadFromFile((entry.path().string()).c_str()))
				{
					printf("Problem with bitmap: #%i\n", idx);
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
						bmp->SetSize(1, 1);
					}
				}

				spri.push_back(std::make_pair(idx, bmp));
				sprf++;
			}
		}
	}

	std::sort(spri.begin(), spri.end(), [](
		const std::pair<uint32_t, std::shared_ptr<BMP>>& fspr, 
		const std::pair<uint32_t, std::shared_ptr<BMP>>& sspr)
	{
		return (fspr.first < sspr.first);
	});

	auto it = std::unique(spri.begin(), spri.end(), [](
		const std::pair<uint32_t, std::shared_ptr<BMP>>& fspr, 
		const std::pair<uint32_t, std::shared_ptr<BMP>>& sspr)
	{
		return fspr.first == sspr.first;
	});

	spri.erase(it, spri.end());

	sprs = spri.size();
	printf("Imported %i sprites\n", sprs);

	if ((sprs >= 1614 && sprs <= 3000) && m_IsHFX == false)
	{
		auto result = System::Windows::Forms::MessageBox::Show("Is this an HFX bank?", "Bank Type", System::Windows::Forms::MessageBoxButtons::YesNo, System::Windows::Forms::MessageBoxIcon::Information);
		if (result == System::Windows::Forms::DialogResult::Yes)
			g_Sprite.SetHFX(true);
	}

	spro = sizeof(CSprite::BankHeader) + (sizeof(CSprite::TbSprite) * sprf);
	printf("Offset starting at %#04X\n", spro);

	printf("Writing data, please wait..\n");
	std::ofstream ofs(path, std::ios::binary | std::ios::trunc);
	if (ofs.is_open())
	{
		ofs.write(reinterpret_cast<const char*>(&szMagic), sizeof(char) * 4);
		ofs.write(reinterpret_cast<const char*>(&sprf), sizeof(uint32_t));

		for (uint32_t i = 0; i < sprf; i++)
		{
			sprw = spri[i].second->TellWidth();
			sprh = spri[i].second->TellHeight();
			ConvertBitmapToData(*spri[i].second, conv, i, sprs);

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

		SetHFX(isHFX);
		printf("Created sprite bank file\n");
		ofs.close();
	}
	else
	{
		printf("Failed to open output stream. Sprite bank file was NOT created\n");
		SetHFX(isHFX);
	}
}

bool CSprite::IsPixelEmpty(const RGBApixel& rgb)
{
	if (rgb.Red == 0 &&
		rgb.Green == 255 &&
		rgb.Blue == 255)
	{
		return true;
	}

	return false;
}

bool CSprite::IsPixelColorKey(const RGBApixel& rgb)
{
	if (rgb.Red == 255 &&
		rgb.Green == 0 &&
		rgb.Blue == 255)
	{
		return true;
	}

	return false;
}

int32_t CSprite::findSection(const int32_t& offset, BMP& sheet)
{
	RGBApixel rgb;
	auto height = sheet.TellHeight();

	for (int32_t y = offset + 1; y < height; y++)
	{
		rgb = sheet.GetPixel(0, y); 
		if (IsPixelColorKey(rgb))
		{
			return y;
		}
	}

	return height;
}

bool CSprite::SheetExtract(const std::string& filePath, const std::string& outputPath, bool rekey, uint32_t startIndex)
{
	BMP sheet;
	RGBApixel rgb;
	int32_t sy = 0
		, psy = 0
		, shw, shy
		, sprw, sprh
		, count = startIndex;
	Vector2 vL, vR;
	bool column_empty;

	auto reset = [&]() {
		memset(&vL, 0, sizeof(Vector2));
		memset(&vR, 0, sizeof(Vector2));
		sprw = 0;
		sprh = 0;
	};

	if (sheet.ReadFromFile(filePath.c_str()))
	{
		shw = sheet.TellWidth();
		shy = sheet.TellHeight();
		sy = findSection(sy, sheet);

		for (int32_t x = 0; x < shw; x++)
		{
			column_empty = true;

			for (int32_t y = sy-1; y != 0; y--)
			{
				if (y == psy)
					break;

				rgb = sheet.GetPixel(x, y);
				if (!IsPixelEmpty(rgb))
				{
					column_empty = false;

					if (vL.x == 0)
						vL.x = x;

					if (y > vL.y || !vL.y)
						vL.y = y;

					if (y < vR.y || !vR.y)
						vR.y = y;
				}
			}

			if ((column_empty && *((int32_t*)&vL)) || 
				(x + 1) > shw)
			{
				vR.x = x;

				sprw = vR.x - vL.x;
				sprh = vL.y - vR.y;
				sprh += 1;

				BMP spr;
				spr.SetBitDepth(24);
				spr.SetSize(sprw, sprh);
			
				for (uint32_t i = 0; i < sprw; i++)
				{
					for (uint32_t j = 0; j < sprh; j++)
					{ 
						rgb = sheet.GetPixel(vL.x + i, vR.y + j);

						if (rekey && IsPixelEmpty(rgb))
						{
							rgb.Red = 255;
							rgb.Green = 0;
							rgb.Blue = 255;
						}
							
						spr.SetPixel(i, j, rgb);
					}
				}

				spr.WriteToFile((outputPath + "//" + std::to_string(count) + ".bmp").c_str());
				count++;
				reset();
			}

			if ((x + 2) > shw)
			{
				if (sy == shy)
					break;

				x = 0;
				psy = sy;
				sy = findSection(sy+1, sheet);
			}
		}

		printf("Finished parsing sprite sheet. Found %i sprites\n", count);
		return true;
	}

	printf("Problem loading sprite sheet:\n    %s\n", filePath.c_str());
	return false;
}

void CSprite::SheetCreate(const std::string& filePath, const std::string& sourcePath)
{
	BMP sheet;
	uint16_t sprs
		, sprw, sprh
		, hh = 0
		, cx = 1, cy = 1
		, shw = 0, shy = 0;
	std::vector<std::pair<uint32_t, std::shared_ptr<BMP>>> vecSprs;

	for (const auto & entry : std::filesystem::directory_iterator(sourcePath))
	{
		if (!(entry.is_directory()) && (entry.path().extension() == ".bmp"))
		{
			std::string filename = entry.path().filename().string();
			std::string tmp = filename.substr(0, filename.find(".", 0));

			if (std::all_of(tmp.begin(), tmp.end(), isdigit))
			{
				uint32_t idx = std::stoi(tmp);
				auto bmp = std::make_shared<BMP>();
				if (!bmp->ReadFromFile((entry.path().string()).c_str()))
				{
					printf("Failed to open:\n    %s, skipping\n", tmp.c_str());
					continue;
				}

				vecSprs.push_back(std::make_pair(idx, bmp));
			}
		}
	}

	std::sort(vecSprs.begin(), vecSprs.end(), [](
		const std::pair<uint32_t, std::shared_ptr<BMP>>& fspr,
		const std::pair<uint32_t, std::shared_ptr<BMP>>& sspr)
	{
		return (fspr.first < sspr.first);
	});

	auto it = std::unique(vecSprs.begin(), vecSprs.end(), [](
		const std::pair<uint32_t, std::shared_ptr<BMP>>& fspr,
		const std::pair<uint32_t, std::shared_ptr<BMP>>& sspr)
	{
		return fspr.first == sspr.first;
	});

	vecSprs.erase(it, vecSprs.end());

	sprs = vecSprs.size();

#define PAD_X	(4)
#define	PAD_Y	(6)

	for (uint32_t i = 0; i < sprs; i++)
	{
		auto spr = vecSprs[i].second;
		sprw = spr->TellWidth();
		sprh = spr->TellHeight();

		if ((cx + sprw + PAD_X) < 1000)
		{
			cx += sprw + PAD_X;

			if (shw < cx)
				shw = cx;

			if (hh < sprh)
				hh = sprh;
		}
		else
		{
			cx = 1;
			cy += hh + PAD_Y;
			hh = 0;

			i--;
		}

		if ((sprh + cy + PAD_Y) > shy)
			shy = sprh + cy + PAD_Y + 1;
	}

	printf("Creating sprite sheet (%i sprites) with a size of %ix%i\n", sprs, shw, shy);
	sheet.SetBitDepth(24);
	sheet.SetSize(shw, shy);

	RGBApixel rgb;
	rgb.Red = 0;
	rgb.Green = 255;
	rgb.Blue = 255;
	rgb.Alpha = 255;
	for (uint32_t x = 0; x < shw; x++)
	{
		for (uint32_t y = 0; y < shy; y++)
		{
			sheet.SetPixel(x, y, rgb);
		}
	}

	cx = 1, cy = 1; 
	hh = 0;
	for (uint32_t i = 0; i < sprs; i++)
	{
		auto spr = vecSprs[i].second;
		sprw = spr->TellWidth();
		sprh = spr->TellHeight();

		if ((cx + sprw + PAD_X) < shw)
		{
			for (uint32_t x = 0; x < sprw; x++)
			{
				for (uint32_t y = 0; y < sprh; y++)
				{
					sheet.SetPixel(cx + x, cy + y, spr->GetPixel(x, y));
				}
			}

			cx += sprw + PAD_X;

			if (hh < sprh)
				hh = sprh;
		}
		else
		{
			cx = 1;
			cy += hh + PAD_Y;
			hh = 0;

			for (uint32_t x = 0; x < shw; x++)
			{
				sheet.SetPixel(x, cy - (PAD_Y/2), {255, 0, 255, 255});
			}

			i--;
		}
	}

	sheet.WriteToFile(filePath.c_str());
	printf("Created sprite sheet:\n    %s\n", filePath.c_str());
}

bool CSprite::IsAlphaSprite(uint32_t index)
{
	if (m_IsHFX)
	{
		if (index >= 1090 && index <= 1499 ||
			index >= 1538 && index <= 1592)
		{
			return true;
		}
	}

	return false;
}