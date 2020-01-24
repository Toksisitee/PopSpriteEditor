#pragma once

class CSprite
{
public:
	CSprite() {};
	~CSprite() {};

	struct TbSprite
	{
		uint16_t	Width;
		uint16_t	Height;
		uint32_t	Offset;
	};

	struct DATA
	{
		TbSprite	Sprite;
		int8_t*		Data;
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
	void Clear() { delete[] m_pBuffer; SprBank.Data.clear(); }

private:
	char* m_pBuffer;
	uint32_t m_nBufferLength;
};