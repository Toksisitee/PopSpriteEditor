#pragma once

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
	void SaveSprite(uint16_t index);
	void DumpMemoryToBank(std::string& path);
	void ImportToBank(std::string& path);
	void ConvertBitmapToData(bitmap_image sprbmp, std::vector<uint8_t>& vec);
	System::Drawing::Bitmap^ getSpriteBitmapHandle(uint16_t index);
	void Clear() { delete[] m_pBuffer; SprBank.Data.clear(); }

private:
	char* m_pBuffer;
	uint32_t m_nBufferLength;
};