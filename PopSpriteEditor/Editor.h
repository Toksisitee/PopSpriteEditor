#pragma once
#include <cstdint>

#define TO_STRING(s)	#s
#define STRINGIFY(s)	TO_STRING(s)

#define VERSION_MAJOR	1
#define VERSION_MINOR	2
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