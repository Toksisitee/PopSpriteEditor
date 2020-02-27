#pragma once
#include <vector>
#include "EasyBMP/EasyBMP.h"

#define RPAL	(0)
#define RREAD	(1)
#define RSKIP	(2)
#define REND	(3)

class CSprite
{
public:
	CSprite() {};
	~CSprite() {};

	typedef std::vector<std::vector<int32_t>> MAP;

	struct RAW
	{
		uint8_t	Data;
		int8_t  Type;
	};

	struct TbSprite
	{
		uint16_t	Width;
		uint16_t	Height;
		uint32_t	Offset;
	};

	struct DATA
	{
		TbSprite			Sprite;
		int8_t*				Data;
		std::vector<RAW>	Raw;
		MAP					Map;
	};

	struct BankHeader
	{
		char		Magic[4];
		uint32_t	Frames;
	};

	struct Bank
	{
		BankHeader Header;
		std::vector<DATA> Data;
	};

	Bank SprBank;
	bool LoadBank(const std::string& file);
	void MapSprite(uint16_t index);
	void ExportSprite(uint16_t index);
	void ExportSprites();
	void DumpMemoryToBank(std::string& path);
	void ImportToBank(std::string& path);
	void ConvertBitmapToData(BMP sprbmp, std::vector<uint8_t>& vec, int32_t index, uint32_t maxIndex);
	System::Drawing::Bitmap^ getSpriteBitmapHandle(uint16_t index);
	bool SheetExtract(const std::string& filePath, const std::string& outputPath, bool rekey, uint32_t startIndex);
	void SheetCreate(const std::string& filePath, const std::string& sourcePath);
	void Clear() { delete[] m_pBuffer; SprBank.Data.clear(); }

private:
	char* m_pBuffer;
	uint32_t m_nBufferLength;
	int32_t findSection(const int32_t& offset, BMP& sheet);
	bool IsPixelColorKey(const RGBApixel& rgb);
	bool IsPixelEmpty(const RGBApixel& rgb);
};

extern CSprite g_Sprite;