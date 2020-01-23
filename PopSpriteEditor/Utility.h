#pragma once
#include <string>
#define NOMINMAX
#include "Windows.h"

extern std::string GetCurrentDir();
extern bool FileExists(const std::string& file);