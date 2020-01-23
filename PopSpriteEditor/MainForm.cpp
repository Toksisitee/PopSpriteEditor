#include "MainForm.h"
#include "bitmap_image.hpp"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<System::String^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	PopSpriteEditor::GlobalForms::MainWindow = gcnew PopSpriteEditor::MainForm();
	Application::Run(PopSpriteEditor::GlobalForms::MainWindow);
	return 0;
}