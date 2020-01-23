#include "Utility.h"

std::string GetCurrentDir()
{
	char buffer[256];
	GetCurrentDirectoryA(256, buffer);
	return (std::string(buffer) + '\\');
}

bool FileExists(const std::string& file)
{
	struct stat buffer;
	return (stat(file.c_str(), &buffer) == 0);
}