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
	private: System::Windows::Forms::LinkLabel^  linkLabelTok;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::RichTextBox^  ctrlAboutRichText;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  VersionLabel;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::LinkLabel^  linkLabelBmp;


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
			this->linkLabelTok = (gcnew System::Windows::Forms::LinkLabel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ctrlAboutRichText = (gcnew System::Windows::Forms::RichTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->VersionLabel = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->linkLabelBmp = (gcnew System::Windows::Forms::LinkLabel());
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
			// linkLabelTok
			// 
			this->linkLabelTok->AutoSize = true;
			this->linkLabelTok->LinkBehavior = System::Windows::Forms::LinkBehavior::AlwaysUnderline;
			this->linkLabelTok->Location = System::Drawing::Point(107, 239);
			this->linkLabelTok->Name = L"linkLabelTok";
			this->linkLabelTok->Size = System::Drawing::Size(55, 13);
			this->linkLabelTok->TabIndex = 8;
			this->linkLabelTok->TabStop = true;
			this->linkLabelTok->Text = L"Toksisitee";
			this->linkLabelTok->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &AboutForm::linkLabel2_LinkClicked);
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
			this->ctrlAboutRichText->Location = System::Drawing::Point(12, 307);
			this->ctrlAboutRichText->Name = L"ctrlAboutRichText";
			this->ctrlAboutRichText->Size = System::Drawing::Size(380, 142);
			this->ctrlAboutRichText->TabIndex = 6;
			this->ctrlAboutRichText->Text = L"";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 261);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(45, 13);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Version:";
			// 
			// VersionLabel
			// 
			this->VersionLabel->AutoSize = true;
			this->VersionLabel->Location = System::Drawing::Point(107, 261);
			this->VersionLabel->Name = L"VersionLabel";
			this->VersionLabel->Size = System::Drawing::Size(22, 13);
			this->VersionLabel->TabIndex = 11;
			this->VersionLabel->Text = L"1.0";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 283);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(49, 13);
			this->label4->TabIndex = 12;
			this->label4->Text = L"Libraries:";
			// 
			// linkLabelBmp
			// 
			this->linkLabelBmp->AutoSize = true;
			this->linkLabelBmp->LinkBehavior = System::Windows::Forms::LinkBehavior::AlwaysUnderline;
			this->linkLabelBmp->Location = System::Drawing::Point(107, 283);
			this->linkLabelBmp->Name = L"linkLabelBmp";
			this->linkLabelBmp->Size = System::Drawing::Size(53, 13);
			this->linkLabelBmp->TabIndex = 13;
			this->linkLabelBmp->TabStop = true;
			this->linkLabelBmp->Text = L"EasyBMP";
			this->linkLabelBmp->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &AboutForm::linkLabel2_LinkClicked);
			// 
			// AboutForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(404, 461);
			this->Controls->Add(this->linkLabelBmp);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->VersionLabel);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->linkLabelTok);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ctrlAboutRichText);
			this->Controls->Add(this->ctrlAboutIcon);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(420, 500);
			this->MinimumSize = System::Drawing::Size(420, 500);
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
