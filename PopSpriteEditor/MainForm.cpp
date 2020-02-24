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
#include "EasyBMP/EasyBMP.h"
#include "Utility.h"
#include "Sprite.h"
#include "Palette.h"
#include "AboutForm.h"
#include "Editor.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;

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

CSprite g_Sprite;
gcroot<System::String^> g_InitialDirectory = nullptr;
gcroot<ToolTip^> g_PixelTip = nullptr;
gcroot<System::Drawing::Bitmap^> g_BitmapPalette = nullptr;
gcroot<System::Drawing::Bitmap^> g_BitmapSprite = nullptr;

Editor g_Editor;
std::vector<EditBuffer> g_EditUndo;
std::vector<EditBuffer>	g_EditRedo;

ScreenPixel g_ScrPixel;

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

bool OnMouseLeftRight(System::Windows::Forms::MouseEventArgs ^ e)
{
	if (e->Button == System::Windows::Forms::MouseButtons::Left ||
		e->Button == System::Windows::Forms::MouseButtons::Right)
	{
		return true;
	}

	return false;
}

System::Void PopSpriteEditor::MainForm::OnEditorButtonReset()
{
	ctrlBtnPaint->FlatAppearance->BorderColor = Color::Black;
	ctrlBtnCursor->FlatAppearance->BorderColor = Color::Black;
	ctrlBtnColorPick->FlatAppearance->BorderColor = Color::Black;
}

void OnSpritePaint(uint16_t sprIndex, bool mainSlot)
{
	if (g_Editor.Mode == EDITOR_MODE_PAINT)
	{
		if (g_EditUndo.size() >= EDITOR_MAX_BUFFER)
		{
			g_EditUndo.erase(g_EditUndo.begin());
		}

		auto clrIndex = mainSlot == true ? g_Editor.ColorIndex : g_Editor.ColorIndex2;
		uint8_t pal = g_Sprite.SprBank.Data[sprIndex].Map[g_ScrPixel.x][g_ScrPixel.y];
		g_EditUndo.push_back({ g_ScrPixel.x, g_ScrPixel.y, sprIndex, pal });
		g_Sprite.SprBank.Data[sprIndex].Map[g_ScrPixel.x][g_ScrPixel.y] = clrIndex;
	}
}

void OnColorSelect(bool mainSlot)
{
	PictureBox^ box;
	auto slot = mainSlot == true ? &g_Editor.ColorIndex : &g_Editor.ColorIndex2;
	*slot = g_ScrPixel.palIndex;

	if (mainSlot)
		box = PopSpriteEditor::GlobalForms::MainWindow->ctrlPaintColor;
	else 
		box = PopSpriteEditor::GlobalForms::MainWindow->ctrlPaintColor2;

	box->BackColor = System::Drawing::Color::FromArgb(
			255,
			g_Palette[*slot].R,
			g_Palette[*slot].G,
			g_Palette[*slot].B
		);
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

inline System::Void PopSpriteEditor::MainForm::openToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	auto dialog = gcnew OpenFileDialog();
	dialog->Title = "Open Sprite Bank";
	dialog->Filter = "Data|*.dat|Sprite|*.spr";

	if (static_cast<String^>(g_InitialDirectory) == nullptr)
		dialog->InitialDirectory = Directory::GetCurrentDirectory();
	else
		dialog->InitialDirectory = g_InitialDirectory;

	if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		g_InitialDirectory = dialog->FileName;
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

	g_EditUndo.clear();
	g_ScrPixel.processed = true;
	g_ScrPixel.x = 0;
	g_ScrPixel.y = 0;

	uint16_t selectedIndex = ctrlListSprites->FocusedItem->Index;
	g_Sprite.MapSprite(selectedIndex);

	ctrlGroupBoxSelect->Text = "Sprite: #" + selectedIndex.ToString();
	ctrlSpriteImg->Invalidate();
	ctrlSpriteImg2->Invalidate();

	if (debugDataToolStripMenuItem->Checked)
	{
		System::String^ hexByte;
		std::vector<uint8_t> bmpData;
		BMP bmp;
		bmp.ReadFromFile((GetCurrentDir() + "output\\" + std::to_string(selectedIndex) + ".bmp").c_str());
		g_Sprite.ConvertBitmapToData(bmp, bmpData, selectedIndex, g_Sprite.SprBank.Header.Frames);

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


	if (g_ScrPixel.processed != true)
	{
		if ((g_ScrPixel.x >= 0) && (g_ScrPixel.x < bmp->Width) && (g_ScrPixel.y >= 0) && (g_ScrPixel.y < bmp->Height))
		{
			auto rgb = g_ScrPixel.rgb;
			uint8_t alpha = 150;

			if (g_Editor.Mode == EDITOR_MODE_PAINT)
			{
				rgb = g_Palette[g_Editor.ColorIndex];
				alpha = 255;
			}

			bmp->SetPixel(g_ScrPixel.x, g_ScrPixel.y,
				System::Drawing::Color::FromArgb(
					alpha, rgb.R, rgb.G, rgb.B)
			);
		}

		g_ScrPixel.processed = true;
	}

	auto g = e->Graphics;
	g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
	g->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::Half;
	g->DrawImage(bmp, 0, 0, bmp->Width * scaleFactor, bmp->Height * scaleFactor);
	g_BitmapSprite = bmp;
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

	if (g_ScrPixel.processed != true)
	{
		if ((g_ScrPixel.x >= 0) && (g_ScrPixel.x < bmp->Width) && (g_ScrPixel.y >= 0) && (g_ScrPixel.y < bmp->Height))
		{
			bmp->SetPixel(g_ScrPixel.x, g_ScrPixel.y,
				System::Drawing::Color::FromArgb(
					150,
					g_ScrPixel.rgb.R,
					g_ScrPixel.rgb.G,
					g_ScrPixel.rgb.B)
			);
		}

		g_ScrPixel.processed = true;
	}

	g->DrawImage(bmp, static_cast<int32_t>((ctrlPaletteImg->Width - (bmp->Width * scaleFactor)) / 2),
		static_cast<int32_t>((ctrlPaletteImg->Height - (bmp->Height * scaleFactor)) / 2),
		static_cast<int32_t>(bmp->Width * scaleFactor),
		static_cast<int32_t>(bmp->Height * scaleFactor));

	g_BitmapPalette = bmp;
}

inline System::Void PopSpriteEditor::MainForm::MainForm_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	GlobalForms::MainWindow->Text = "PopSpriteEditor - v" + EDITOR_VERSION;
	ctrlSpriteImg->BackColor = Color::White;
	ctrlSpriteImg2->BackColor = Color::White;
	ctrlPaletteImg->BackColor = Color::White;
	ctrlPaintColor->BackColor = Color::Fuchsia;
	ctrlPaintColor2->BackColor = Color::Fuchsia;
	debugDataToolStripMenuItem_CheckedChanged(nullptr, nullptr);
	g_PixelTip = gcnew ToolTip();
	g_PixelTip->ShowAlways = true;

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
	printf("Exporting sprites, please wait..\n");
	for (uint32_t i = 0; i < g_Sprite.SprBank.Header.Frames; i++)
	{
		g_Sprite.SaveSprite(i);
	}
	printf("Done\n");
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

inline System::Void PopSpriteEditor::MainForm::ctrlListSprites_MouseClick(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e) 
{
	if (e->Button == System::Windows::Forms::MouseButtons::Right)
	{
		if (ctrlListSprites->FocusedItem->Bounds.Contains(e->Location))
		{
			ctrlListSpritesContext->Show(Cursor->Position);
		}
	}
}

inline System::Void PopSpriteEditor::MainForm::CopyOffset_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	if (ctrlListSprites->SelectedItems->Count == 0)
		return;

	uint16_t selectedIndex = ctrlListSprites->FocusedItem->Index;
	System::Windows::Forms::Clipboard::SetText(g_Sprite.SprBank.Data[selectedIndex].Sprite.Offset.ToString("X2"));
}

inline System::Void PopSpriteEditor::MainForm::toolStripTextBox1_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e) 
{
	e->Handled = !Char::IsDigit(e->KeyChar) && !Char::IsControl(e->KeyChar);
}

inline System::Void PopSpriteEditor::MainForm::toolStripTextBox1_TextChanged(System::Object ^ sender, System::EventArgs ^ e) 
{
	ToolStripTextBox^ box = safe_cast<ToolStripTextBox^>(sender);
	auto index = UInt32::Parse(box->Text);

	if (index > ((sizeof(g_Palette) / sizeof(g_Palette[0])) - 1))
	{
		index = 255;
		box->Text = "255";
	}

	Palette::ColorKeys[2] = index;
}

inline System::Void PopSpriteEditor::MainForm::ctrlPaletteImg_MouseMove(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e) 
{
	if (static_cast<System::Drawing::Bitmap^>(g_BitmapPalette) != nullptr)
	{
		auto bmp = g_BitmapPalette;
		double scaleX = (double)ctrlPaletteImg->Width / (double)bmp->Height;
		double scaleY = (double)ctrlPaletteImg->Height / (double)bmp->Width;
		double scaleFactor = scaleX < scaleY ? scaleX : scaleY;
		auto x = static_cast<int32_t>((ctrlPaletteImg->Width - (bmp->Width * scaleFactor)) / 2);
		auto y = static_cast<int32_t>((ctrlPaletteImg->Height - (bmp->Height * scaleFactor)) / 2);
		x = (e->X - x) / scaleFactor;
		y = (e->Y - y) / scaleFactor;

		if (g_ScrPixel.x != x || g_ScrPixel.y != y)
		{
			if ((x >= 0) && (x < bmp->Width) && (y >= 0) && (y < bmp->Height))
			{
				auto rgb = g_BitmapPalette->GetPixel(x, y);
				auto index = Palette::FindColorAll({ rgb.R, rgb.G, rgb.B });
				g_PixelTip->SetToolTip(ctrlPaletteImg, " ");
				g_PixelTip->ToolTipTitle = "W: " + x + " H: " + y;
				g_PixelTip->SetToolTip(ctrlPaletteImg, "RGB: " + rgb.R + " " + rgb.G + " " + rgb.B + "\nIndex: " + index);

				g_ScrPixel.x = x;
				g_ScrPixel.y = y;
				g_ScrPixel.rgb = { rgb.R, rgb.G, rgb.B };
				g_ScrPixel.palIndex = index;
				g_ScrPixel.processed = false;


				if (g_Editor.Mode == EDITOR_MODE_PAINT || 
					g_Editor.Mode == EDITOR_MODE_COLOR_PICK)
				{
					if (OnMouseLeftRight(e))
					{
						bool mainSlot = e->Button == System::Windows::Forms::MouseButtons::Left ? true : false;
						OnColorSelect(mainSlot);
					}
				}

				ctrlPaletteImg->Invalidate();
			}
		}
	}
}

inline System::Void PopSpriteEditor::MainForm::ctrlSpriteImg2_MouseMove(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e) 
{
	if (static_cast<System::Drawing::Bitmap^>(g_BitmapSprite) != nullptr)
	{
		auto bmp = g_BitmapSprite;
		uint8_t scaleFactor = ctrlSpriteSize->Value;
		int32_t x = (e->X - 0) / scaleFactor;
		int32_t y = (e->Y - 0) / scaleFactor;

		if (g_ScrPixel.x != x || g_ScrPixel.y != y)
		{
			if ((x >= 0) && (x < bmp->Width) && (y >= 0) && (y < bmp->Height))
			{
				auto rgb = g_BitmapSprite->GetPixel(x, y);
				auto index = Palette::FindColorAll({ rgb.R, rgb.G, rgb.B });
				g_PixelTip->SetToolTip(ctrlSpriteImg2, " ");
				g_PixelTip->ToolTipTitle = "W: " + x + " H: " + y;
				g_PixelTip->SetToolTip(ctrlSpriteImg2, "RGB: " + rgb.R + " " + rgb.G + " " + rgb.B + "\nIndex: " + index);

				g_ScrPixel.x = x;
				g_ScrPixel.y = y;
				g_ScrPixel.rgb = { rgb.R, rgb.G, rgb.B };
				g_ScrPixel.palIndex = index;
				g_ScrPixel.processed = false;

				if (ctrlListSprites->SelectedItems->Count != 0)
				{
					if (OnMouseLeftRight(e))
					{
						bool mainSlot = e->Button == System::Windows::Forms::MouseButtons::Left ? true : false;
						OnSpritePaint(ctrlListSprites->FocusedItem->Index, mainSlot);
					}
				}

				ctrlSpriteImg2->Invalidate();
			}
		}
	}
}

inline System::Void PopSpriteEditor::MainForm::ctrlPaletteImg_MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e) 
{
	if (g_Editor.Mode == EDITOR_MODE_NORMAL)
	{
		if (g_ScrPixel.palIndex != -1)
		{
			ctrlTooltipContext->Show(Cursor->Position);
		}
	}
	else if (g_Editor.Mode == EDITOR_MODE_PAINT ||
		g_Editor.Mode == EDITOR_MODE_COLOR_PICK)
	{
		if (OnMouseLeftRight(e))
		{
			bool mainSlot = e->Button == System::Windows::Forms::MouseButtons::Left ? true : false;
			OnColorSelect(mainSlot);
		}
	}
}

inline System::Void PopSpriteEditor::MainForm::copyRGBToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	System::Windows::Forms::Clipboard::SetText(g_ScrPixel.rgb.R.ToString() + ", " + g_ScrPixel.rgb.G.ToString() + ", " + g_ScrPixel.rgb.B.ToString());
}

inline System::Void PopSpriteEditor::MainForm::ctrlSpriteImg2_MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e) 
{
	if (g_Editor.Mode == EDITOR_MODE_NORMAL)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			if (g_ScrPixel.palIndex != -1)
			{
				ctrlTooltipContext->Show(Cursor->Position);
			}
		}
	}
	else if (g_Editor.Mode == EDITOR_MODE_PAINT)
	{
		if (ctrlListSprites->SelectedItems->Count != 0)
		{
			if (OnMouseLeftRight(e))
			{
				bool mainSlot = e->Button == System::Windows::Forms::MouseButtons::Left ? true : false;
				OnSpritePaint(ctrlListSprites->FocusedItem->Index, mainSlot);
			}
		}
	}
	else if (g_Editor.Mode == EDITOR_MODE_COLOR_PICK)
	{
		if (OnMouseLeftRight(e))
		{
			bool mainSlot = e->Button == System::Windows::Forms::MouseButtons::Left ? true : false;
			OnColorSelect(mainSlot);
		}
	}
}

inline System::Void PopSpriteEditor::MainForm::exportPaletteToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	Palette::Save(g_Palette);
}

inline System::Void PopSpriteEditor::MainForm::MainForm_KeyDown(System::Object ^ sender, System::Windows::Forms::KeyEventArgs ^ e) 
{
	if ((e->Control) && e->KeyCode == Keys::Z)
	{
		if (g_EditUndo.size() > 0)
		{
			if (ctrlListSprites->SelectedItems->Count == 0)
				return;

			auto buffer = g_EditUndo.back();
			EditBuffer buf;
			buf.palIndex = g_Sprite.SprBank.Data[buffer.sprIndex].Map[buffer.x][buffer.y];
			buf.sprIndex = buffer.sprIndex;
			buf.x = buffer.x;
			buf.y = buffer.y;
			g_EditRedo.push_back(buf);

			if (g_EditRedo.size() >= EDITOR_MAX_BUFFER)
			{
				g_EditRedo.erase(g_EditRedo.begin());
			}

			g_Sprite.SprBank.Data[buffer.sprIndex].Map[buffer.x][buffer.y] = buffer.palIndex;
			g_EditUndo.pop_back();

			ctrlSpriteImg2->Invalidate();
		}
	}
	else if ((e->Control) && e->KeyCode == Keys::Y)
	{
		if (g_EditRedo.size() > 0)
		{
			if (ctrlListSprites->SelectedItems->Count == 0)
				return;

			auto buffer = g_EditRedo.back();

			EditBuffer buf;
			buf.palIndex = g_Sprite.SprBank.Data[buffer.sprIndex].Map[buffer.x][buffer.y];
			buf.sprIndex = buffer.sprIndex;
			buf.x = buffer.x;
			buf.y = buffer.y;
			g_EditUndo.push_back(buf);

			if (g_EditUndo.size() >= EDITOR_MAX_BUFFER)
			{
				g_EditUndo.erase(g_EditUndo.begin());
			}

			g_Sprite.SprBank.Data[buffer.sprIndex].Map[buffer.x][buffer.y] = buffer.palIndex;
			g_EditRedo.pop_back();

			ctrlSpriteImg2->Invalidate();
		}
	}
}

inline System::Void PopSpriteEditor::MainForm::ctrlBtnPaint_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	OnEditorButtonReset();
	g_Editor.Mode = EDITOR_MODE_PAINT;
	ctrlPaletteImg->Cursor = Cursors::Hand;
	ctrlSpriteImg2->Cursor = Cursors::Hand;
	ctrlBtnPaint->FlatAppearance->BorderColor = Color::Red;
}

inline System::Void PopSpriteEditor::MainForm::ctrlBtnCursor_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	OnEditorButtonReset();
	g_Editor.Mode = EDITOR_MODE_NORMAL;
	Cursor->Current = Cursors::Arrow;
	ctrlPaletteImg->Cursor = Cursors::Arrow;
	ctrlSpriteImg2->Cursor = Cursors::Arrow;
	ctrlBtnCursor->FlatAppearance->BorderColor = Color::Red;
}

inline System::Void PopSpriteEditor::MainForm::ctrlBtnColorPick_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	OnEditorButtonReset();
	g_Editor.Mode = EDITOR_MODE_COLOR_PICK;
	ctrlPaletteImg->Cursor = Cursors::Cross;
	ctrlSpriteImg2->Cursor = Cursors::Cross;
	ctrlBtnColorPick->FlatAppearance->BorderColor = Color::Red;
}

