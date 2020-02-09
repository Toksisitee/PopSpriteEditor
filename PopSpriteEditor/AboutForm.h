#pragma once

namespace PopSpriteEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for AboutForm
	/// </summary>
	public ref class AboutForm : public System::Windows::Forms::Form
	{
	public:
		AboutForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AboutForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  ctrlAboutIcon;
	protected:
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::LinkLabel^  linkLabel2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::RichTextBox^  ctrlAboutRichText;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  VersionLabel;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(AboutForm::typeid));
			this->ctrlAboutIcon = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->linkLabel2 = (gcnew System::Windows::Forms::LinkLabel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ctrlAboutRichText = (gcnew System::Windows::Forms::RichTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->VersionLabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlAboutIcon))->BeginInit();
			this->SuspendLayout();
			// 
			// ctrlAboutIcon
			// 
			this->ctrlAboutIcon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ctrlAboutIcon.Image")));
			this->ctrlAboutIcon->Location = System::Drawing::Point(12, 12);
			this->ctrlAboutIcon->Name = L"ctrlAboutIcon";
			this->ctrlAboutIcon->Size = System::Drawing::Size(380, 215);
			this->ctrlAboutIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->ctrlAboutIcon->TabIndex = 1;
			this->ctrlAboutIcon->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(168, 239);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(116, 13);
			this->label2->TabIndex = 9;
			this->label2->Text = L"<meypcm@gmail.com>";
			// 
			// linkLabel2
			// 
			this->linkLabel2->AutoSize = true;
			this->linkLabel2->LinkBehavior = System::Windows::Forms::LinkBehavior::AlwaysUnderline;
			this->linkLabel2->Location = System::Drawing::Point(107, 239);
			this->linkLabel2->Name = L"linkLabel2";
			this->linkLabel2->Size = System::Drawing::Size(55, 13);
			this->linkLabel2->TabIndex = 8;
			this->linkLabel2->TabStop = true;
			this->linkLabel2->Text = L"Toksisitee";
			this->linkLabel2->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &AboutForm::linkLabel2_LinkClicked);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(11, 239);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(90, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Copyright © 2020";
			// 
			// ctrlAboutRichText
			// 
			this->ctrlAboutRichText->Location = System::Drawing::Point(12, 283);
			this->ctrlAboutRichText->Name = L"ctrlAboutRichText";
			this->ctrlAboutRichText->Size = System::Drawing::Size(380, 116);
			this->ctrlAboutRichText->TabIndex = 6;
			this->ctrlAboutRichText->Text = L"";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 259);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(45, 13);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Version:";
			// 
			// VersionLabel
			// 
			this->VersionLabel->AutoSize = true;
			this->VersionLabel->Location = System::Drawing::Point(107, 259);
			this->VersionLabel->Name = L"VersionLabel";
			this->VersionLabel->Size = System::Drawing::Size(22, 13);
			this->VersionLabel->TabIndex = 11;
			this->VersionLabel->Text = L"1.0";
			// 
			// AboutForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(404, 411);
			this->Controls->Add(this->VersionLabel);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->linkLabel2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ctrlAboutRichText);
			this->Controls->Add(this->ctrlAboutIcon);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(420, 450);
			this->MinimumSize = System::Drawing::Size(420, 450);
			this->Name = L"AboutForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"About";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &AboutForm::AboutForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &AboutForm::AboutForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlAboutIcon))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void AboutForm_Load(System::Object^  sender, System::EventArgs^  e);
private: System::Void linkLabel2_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e);
private: System::Void AboutForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
};
}
