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
#include "AboutForm.h"

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

void HexEditorAppend(System::String^ text, System::Drawing::Color color)
{
	auto editor = PopSpriteEditor::GlobalForms::MainWindow->ctrlHexView;
	editor->SelectionStart = editor->TextLength;
	editor->SelectionLength = 0;
	editor->SelectionColor = color;
	editor->AppendText(text);
	editor->SelectionColor = editor->ForeColor;
	editor->MaxLength = editor->TextLength;
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

	if (debugDataToolStripMenuItem->Checked)
	{
		System::String^ hexByte;
		std::vector<uint8_t> bmpData;

		g_Sprite.ConvertBitmapToData(GetCurrentDir() + "output\\" + std::to_string(selectedIndex) + ".bmp", bmpData);
		ctrlHexBMPView->Clear();
		ctrlSpriteDataBMPLength->Text = "BMP Data (conversion). Length: " + bmpData.size();
		for (auto const& byte : bmpData)
		{
			hexByte = static_cast<int8_t>(byte).ToString("X2") + " ";
			ctrlHexBMPView->AppendText(hexByte);
			ctrlHexBMPView->MaxLength = ctrlHexBMPView->TextLength;
		}

		ctrlHexView->Clear();
		ctrlSpriteDataLength->Text = "Memory Data. Length: " + g_Sprite.SprBank.Data[selectedIndex].Raw.size().ToString();
		for (auto const& byte : g_Sprite.SprBank.Data[selectedIndex].Raw)
		{
			hexByte = byte.Data.ToString("X2") + " ";

			switch (byte.Type)
			{
			case RPAL:
				HexEditorAppend(hexByte, Color::Black);
				break;
			case RREAD:
				HexEditorAppend(hexByte, Color::ForestGreen);
				break;
			case RSKIP:
				HexEditorAppend(hexByte, Color::DarkRed);
				break;
			case REND:
				HexEditorAppend(hexByte, Color::DarkSlateBlue);
				break;
			}
		}

		ctrlSpriteDataMatching->ForeColor = ctrlHexBMPView->Text == ctrlHexView->Text ? Color::DarkGreen : Color::DarkRed;
	}
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
	debugDataToolStripMenuItem_CheckedChanged(nullptr, nullptr);
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

inline System::Void PopSpriteEditor::MainForm::debugDataToolStripMenuItem_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e) 
{
	bool status = debugDataToolStripMenuItem->Checked ? true : false;

	ctrlHexBMPView->Enabled = status;
	ctrlHexView->Enabled = status;
	ctrlSpriteDataBMPLength->Visible = status;
	ctrlSpriteDataLength->Visible = status;
	ctrlSpriteDataMatching->Visible = status;
	ctrlHexBMPView->Visible = status;
	ctrlHexView->Visible = status;

	if (!status)
	{
		ctrlHexBMPView->Clear();
		ctrlHexView->Clear();
	}
}

inline System::Void PopSpriteEditor::MainForm::memoryToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	auto dialog = gcnew SaveFileDialog();
	dialog->Title = "Save Sprite Bank";
	dialog->Filter = "Data|*.dat|Sprite|*.spr";

	if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK &&
		dialog->FileName != "")
	{
		msclr::interop::marshal_context context;
		g_Sprite.DumpMemoryToBank(context.marshal_as<std::string>((dialog->FileName)));
	}
}

inline System::Void PopSpriteEditor::MainForm::dumpSpritesToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	for (uint32_t i = 0; i < g_Sprite.SprBank.Header.Frames; i++)
	{
		g_Sprite.SaveSprite(i);
	}
}

inline System::Void PopSpriteEditor::MainForm::imagesToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	auto dialog = gcnew SaveFileDialog();
	dialog->Title = "Save Sprite Bank";
	dialog->Filter = "Data|*.dat|Sprite|*.spr";

	if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK &&
		dialog->FileName != "")
	{
		msclr::interop::marshal_context context;
		g_Sprite.ImportToBank(context.marshal_as<std::string>((dialog->FileName)));
	}
}

inline System::Void PopSpriteEditor::MainForm::ctrlNumericGoto_KeyDown(System::Object ^ sender, System::Windows::Forms::KeyEventArgs ^ e) 
{
	if (e->KeyCode == Keys::Enter)
	{
		uint16_t spriteIndex = static_cast<uint16_t>(ctrlNumericGoto->Value);
		if (!(ctrlListSprites->Items->Count >= spriteIndex))
		{
			spriteIndex = ctrlListSprites->Items->Count - 1;
			ctrlNumericGoto->Value = spriteIndex;
		}

		ctrlListSprites->FocusedItem = ctrlListSprites->Items[spriteIndex];
		ctrlListSprites->Items[spriteIndex]->Selected = true;
		ctrlListSprites->SelectedItems[0]->Selected = true;
		ctrlListSprites->Select();
		ctrlListSprites->EnsureVisible(spriteIndex);
	}
}

inline System::Void PopSpriteEditor::MainForm::aboutToolStripMenuItem1_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	if (PopSpriteEditor::GlobalForms::AboutWindow == nullptr)
	{
		PopSpriteEditor::GlobalForms::AboutWindow = gcnew PopSpriteEditor::AboutForm();
		PopSpriteEditor::GlobalForms::AboutWindow->Show();
	}
}
