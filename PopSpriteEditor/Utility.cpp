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