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

#include "MainForm.h"
#define NOMINMAX
#include <Windows.h>
#include "bitmap_image.hpp"
#include "Utility.h"
#include "Sprite.h"
#include <msclr\marshal_cppstd.h>

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

inline System::Void PopSpriteEditor::MainForm::openToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	auto dialog = gcnew OpenFileDialog();
	dialog->Title = "Open Sprite Bank";
	dialog->Filter = "Data|*.dat|Sprite|*.spr";
	dialog->InitialDirectory = Directory::GetCurrentDirectory();

	if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		msclr::interop::marshal_context context;
		if (g_Sprite.LoadBank(context.marshal_as<std::string>(dialog->FileName)))
		{
			ctrlListSprites->Items->Clear();
			for (uint32_t i = 0; i < g_Sprite.SprBank.Header.Frames; i++)
			{
				ListViewItem^ item = gcnew ListViewItem(i.ToString());
				item->SubItems->Add(g_Sprite.SprBank.Data[i].Sprite.Offset.ToString("X2"));
				item->SubItems->Add(g_Sprite.SprBank.Data[i].Sprite.Height.ToString());
				item->SubItems->Add(g_Sprite.SprBank.Data[i].Sprite.Width.ToString());
				ctrlListSprites->Items->Add(item);
			}
		}
	}
}
