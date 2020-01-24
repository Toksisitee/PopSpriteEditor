#include "MainForm.h"
#define NOMINMAX
#include <Windows.h>
#include "bitmap_image.hpp"
#include "Utility.h"
#include "Sprite.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;

CSprite g_Sprite;

[STAThreadAttribute]
int main(array<System::String^> ^args)
{
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
	printf("PopSpriteEditor\n");

	std::string bankPath = GetCurrentDir() + "HSPR0-0.dat";
	g_Sprite.LoadBank(bankPath);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Directory::CreateDirectory(Path::Combine(Directory::GetCurrentDirectory(), "output"));

	PopSpriteEditor::GlobalForms::MainWindow = gcnew PopSpriteEditor::MainForm();
	Application::Run(PopSpriteEditor::GlobalForms::MainWindow);
	return 0;
}