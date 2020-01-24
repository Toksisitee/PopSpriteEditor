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
#include <msclr\marshal_cppstd.h>
#include "bitmap_image.hpp"
#include "Utility.h"
#include "Sprite.h"
#include "Palette.h"

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

	std::string palettePath = GetCurrentDir() + "pal.dat";
	Palette::Load(palettePath);

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

inline System::Void PopSpriteEditor::MainForm::ctrlListSprites_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e) 
{
	if (ctrlListSprites->SelectedItems->Count == 0)
		return;

	uint16_t selectedIndex = ctrlListSprites->FocusedItem->Index;
	g_Sprite.MapSprite(selectedIndex);

	ctrlGroupBoxSelect->Text = "Sprite: #" + selectedIndex.ToString();
	ctrlSpriteImg->Invalidate();
	ctrlSpriteImg2->Invalidate();
}

inline System::Void PopSpriteEditor::MainForm::ctrlSpriteImg_Paint(System::Object ^ sender, System::Windows::Forms::PaintEventArgs ^ e) 
{
	if (ctrlListSprites->SelectedItems->Count == 0)
		return;

	auto bmp = g_Sprite.getSpriteBitmapHandle(ctrlListSprites->FocusedItem->Index);
	auto g = e->Graphics;
	g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
	g->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::Half;
	g->Clear(System::Drawing::Color::White);

	double scaleX = (double)ctrlSpriteImg->Width / (double)bmp->Height;
	double scaleY = (double)ctrlSpriteImg->Height / (double)bmp->Width;
	double scaleFactor = scaleX < scaleY ? scaleX : scaleY;

	g->DrawImage(bmp, static_cast<int32_t>((ctrlSpriteImg->Width - (bmp->Width * scaleFactor)) / 2),
		static_cast<int32_t>((ctrlSpriteImg->Height - (bmp->Height * scaleFactor)) / 2),
		static_cast<int32_t>(bmp->Width * scaleFactor),
		static_cast<int32_t>(bmp->Height * scaleFactor));
}

inline System::Void PopSpriteEditor::MainForm::ctrlSpriteImg2_Paint(System::Object ^ sender, System::Windows::Forms::PaintEventArgs ^ e) 
{
	if (ctrlListSprites->SelectedItems->Count == 0)
		return;

	auto bmp = g_Sprite.getSpriteBitmapHandle(ctrlListSprites->FocusedItem->Index);
	uint8_t scaleFactor = ctrlSpriteSize->Value;
	ctrlSpriteImg2->Size = System::Drawing::Size(bmp->Width * scaleFactor, bmp->Height * scaleFactor);
	auto g = e->Graphics;
	g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
	g->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::Half;
	g->DrawImage(bmp, 0, 0, bmp->Width * scaleFactor, bmp->Height * scaleFactor);
}

inline System::Void PopSpriteEditor::MainForm::ctrlPaletteImg_Paint(System::Object ^ sender, System::Windows::Forms::PaintEventArgs ^ e) 
{
	uint32_t b = 0;
	System::Drawing::Bitmap^ bmp = gcnew System::Drawing::Bitmap(16, 16);

	for (uint32_t y = 0; y < 16; y++)
	{
		for (uint32_t x = 0; x < 16; x++)
		{
			auto clr = System::Drawing::Color::FromArgb(
				255,
				g_Palette[b].R,
				g_Palette[b].G,
				g_Palette[b].B
			);

			bmp->SetPixel(x, y, clr);
			b++;
		}
	}

	auto g = e->Graphics;
	g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
	g->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::Half;
	g->Clear(System::Drawing::Color::White);

	double scaleX = (double)ctrlPaletteImg->Width / (double)bmp->Height;
	double scaleY = (double)ctrlPaletteImg->Height / (double)bmp->Width;
	double scaleFactor = scaleX < scaleY ? scaleX : scaleY;

	g->DrawImage(bmp, static_cast<int32_t>((ctrlPaletteImg->Width - (bmp->Width * scaleFactor)) / 2),
		static_cast<int32_t>((ctrlPaletteImg->Height - (bmp->Height * scaleFactor)) / 2),
		static_cast<int32_t>(bmp->Width * scaleFactor),
		static_cast<int32_t>(bmp->Height * scaleFactor));
}

inline System::Void PopSpriteEditor::MainForm::MainForm_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	ctrlSpriteImg->BackColor = Color::White;
	ctrlSpriteImg2->BackColor = Color::White;
	ctrlPaletteImg->BackColor = Color::White;
}

inline System::Void PopSpriteEditor::MainForm::ctrlSpriteSize_ValueChanged(System::Object ^ sender, System::EventArgs ^ e) 
{
	ctrlSpriteImg2->Invalidate();
}

inline System::Void PopSpriteEditor::MainForm::ctrlButtonSaveSprite_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	if (ctrlListSprites->SelectedItems->Count == 0)
		return;

	uint16_t selectedIndex = ctrlListSprites->FocusedItem->Index;
	g_Sprite.SaveSprite(selectedIndex);
}
