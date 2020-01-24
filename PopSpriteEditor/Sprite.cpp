#include <vector>
#include <cstdint>
#include <fstream>
#include "Sprite.h"
#include "Utility.h"

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
