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

#include "SheetForm.h"
#include "MainForm.h"
#include "Sprite.h"
#include <cstdint>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::IO;

inline System::Void PopSpriteEditor::SheetForm::SheetForm_FormClosing(System::Object ^ sender, System::Windows::Forms::FormClosingEventArgs ^ e) 
{
	PopSpriteEditor::GlobalForms::SheetWindow = nullptr;
}

inline System::Void PopSpriteEditor::SheetForm::SheetForm_Load(System::Object ^ sender, System::EventArgs ^ e) 
{
	int16_t sheetDirIndex = -1;
	auto directories = Directory::GetDirectories(Directory::GetCurrentDirectory());

	for (uint16_t i = 0; i < directories->Length; i++)
	{
		directories[i] = directories[i]->Remove(0, directories[i]->LastIndexOf('\\') + 1);

		if (sheetDirIndex == -1 && directories[i] == "sheet-output")
			sheetDirIndex = i;
	}

	ctrlSourceFolder->Items->AddRange(directories);
	ctrlSourceFolder->SelectedIndex = sheetDirIndex == -1 ? 0 : sheetDirIndex;

	ctrlOutputFolder->Items->AddRange(directories);
	ctrlOutputFolder->SelectedIndex = sheetDirIndex == -1 ? 0 : sheetDirIndex;

	ctrlRekey->SelectedIndex = 1;
}

inline System::Void PopSpriteEditor::SheetForm::ctrlCreateSheet_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	auto dialog = gcnew SaveFileDialog();
	dialog->Title = "Save Sprite Sheet";
	dialog->Filter = "Bitmap|*.bmp";

	if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK &&
		dialog->FileName != "")
	{
		msclr::interop::marshal_context context;
		auto sourcePath = Directory::GetCurrentDirectory() + "\\" + ctrlSourceFolder->Text;
		g_Sprite.SheetCreate(context.marshal_as<std::string>(dialog->FileName), context.marshal_as<std::string>(sourcePath));
	}
}

inline System::Void PopSpriteEditor::SheetForm::ctrlSheetExtract_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	auto dialog = gcnew OpenFileDialog();
	dialog->Title = "Open Sprite Sheet";
	dialog->Filter = "Bitmap|*.bmp";
	if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		msclr::interop::marshal_context context;
		auto sourcePath = Directory::GetCurrentDirectory() + "\\" + ctrlOutputFolder->Text + "\\";
		g_Sprite.SheetExtract(context.marshal_as<std::string>(dialog->FileName), 
			context.marshal_as<std::string>(sourcePath), 
			static_cast<bool>(ctrlRekey->SelectedIndex),
			static_cast<uint32_t>(ctrlStartIndex->Value),
			chbExtractBetweenRange->Checked,
			static_cast<uint32_t>(ctrlExtractBetweenRange1->Value), 
			static_cast<uint32_t>(ctrlExtractBetweenRange2->Value),
			chbExtractFromIndex->Checked,
			static_cast<uint32_t>(ctrlExtractFromIndex->Value)
		);
	}
}

inline System::Void PopSpriteEditor::SheetForm::ctrlOpenFolder_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	System::Diagnostics::Process::Start(Directory::GetCurrentDirectory());
}

inline System::Void PopSpriteEditor::SheetForm::chbExtractBetweenRange_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e) 
{
	if (chbExtractBetweenRange->Checked)
	{
		chbExtractFromIndex->Checked = false;
		ctrlExtractBetweenRange1->Enabled = true;
		ctrlExtractBetweenRange2->Enabled = true;
	}
	else
	{
		ctrlExtractBetweenRange1->Enabled = false;
		ctrlExtractBetweenRange2->Enabled = false;
	}
}

inline System::Void PopSpriteEditor::SheetForm::chbExtractFromIndex_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e) 
{
	if (chbExtractFromIndex->Checked)
	{
		chbExtractBetweenRange->Checked = false;
		ctrlExtractFromIndex->Enabled = true;
	}
	else
	{
		ctrlExtractFromIndex->Enabled = false;
	}
}

