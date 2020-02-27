#pragma once
#include <cstdint>

#define TO_STRING(s)	#s
#define STRINGIFY(s)	TO_STRING(s)

#define VERSION_MAJOR	1
#define VERSION_MINOR	3
#define VERSION_PATCH	0

#define EDITOR_VERSION	STRINGIFY(VERSION_MAJOR) "." STRINGIFY(VERSION_MINOR) "." STRINGIFY(VERSION_PATCH)
#define	EDITOR_DATE		__DATE__ " " __TIME__


#define EDITOR_MODE_NORMAL		(0)
#define	EDITOR_MODE_PAINT		(1)
#define EDITOR_MODE_COLOR_PICK	(2)

#define EDITOR_MAX_BUFFER	(200)

struct Vector2
{
	int32_t x = 0;
	int32_t y = 0;
};

struct RGB
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
};

struct ScreenPixel
{
	int32_t x;
	int32_t y;
	uint8_t palIndex;
	RGB rgb;
	bool processed;
};

struct EditBuffer
{
	int32_t x;
	int32_t y;
	uint16_t sprIndex;
	uint8_t palIndex;
};

struct Editor
{
	uint8_t Mode = EDITOR_MODE_NORMAL;
	uint8_t ColorIndex = 255;
	uint8_t ColorIndex2 = 255;
};