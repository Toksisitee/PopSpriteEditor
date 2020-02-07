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

#include "AboutForm.h"
#include "MainForm.h"
#include "Editor.h"

inline System::Void PopSpriteEditor::AboutForm::AboutForm_Load(System::Object ^ sender, System::EventArgs ^ e) 
{
	VersionLabel->Text = EDITOR_VERSION;
	ctrlAboutRichText->Text =
"PopSpriteEditor is free software: you can redistribute it and/or modify\nit under the terms of the GNU General Public License as published by\n\
the Free Software Foundation, either version 3 of the License, or\n\
(at your option) any later version.\n\n\
PopSpriteEditor is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\nSee the \
GNU General Public License for more details.\n\n\
You should have received a copy of the GNU General Public License\n\
along with this program.If not, see < https://www.gnu.org/licenses/>.";
}

inline System::Void PopSpriteEditor::AboutForm::linkLabel2_LinkClicked(System::Object ^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs ^ e) 
{
	System::Diagnostics::Process::Start("https://github.com/Toksisitee");
}

inline System::Void PopSpriteEditor::AboutForm::AboutForm_FormClosing(System::Object ^ sender, System::Windows::Forms::FormClosingEventArgs ^ e) 
{
	PopSpriteEditor::GlobalForms::AboutWindow = nullptr;
}

