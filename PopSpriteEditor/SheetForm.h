#pragma once

namespace PopSpriteEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SheetForm
	/// </summary>
	public ref class SheetForm : public System::Windows::Forms::Form
	{
	public:
		SheetForm(void)
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
		~SheetForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  ctrlCreateSheet;
	private: System::Windows::Forms::Button^  ctrlSheetExtract;
	private: System::Windows::Forms::NumericUpDown^  ctrlStartIndex;
	protected:

	protected:


	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  ctrlRekey;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ComboBox^  ctrlSourceFolder;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  ctrlOutputFolder;
	private: System::Windows::Forms::Button^  ctrlOpenFolder;
	public: System::Windows::Forms::CheckBox^  chbExtractBetweenRange;
	private: System::Windows::Forms::NumericUpDown^  ctrlExtractBetweenRange1;
	private: System::Windows::Forms::NumericUpDown^  ctrlExtractBetweenRange2;
	private: System::Windows::Forms::CheckBox^  chbExtractFromIndex;
	private: System::Windows::Forms::NumericUpDown^  ctrlExtractFromIndex;








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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(SheetForm::typeid));
			this->ctrlCreateSheet = (gcnew System::Windows::Forms::Button());
			this->ctrlSheetExtract = (gcnew System::Windows::Forms::Button());
			this->ctrlStartIndex = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->ctrlRekey = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->ctrlSourceFolder = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->ctrlOutputFolder = (gcnew System::Windows::Forms::ComboBox());
			this->ctrlOpenFolder = (gcnew System::Windows::Forms::Button());
			this->chbExtractBetweenRange = (gcnew System::Windows::Forms::CheckBox());
			this->ctrlExtractBetweenRange1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->ctrlExtractBetweenRange2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->chbExtractFromIndex = (gcnew System::Windows::Forms::CheckBox());
			this->ctrlExtractFromIndex = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlStartIndex))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlExtractBetweenRange1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlExtractBetweenRange2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlExtractFromIndex))->BeginInit();
			this->SuspendLayout();
			// 
			// ctrlCreateSheet
			// 
			this->ctrlCreateSheet->Location = System::Drawing::Point(169, 277);
			this->ctrlCreateSheet->Name = L"ctrlCreateSheet";
			this->ctrlCreateSheet->Size = System::Drawing::Size(91, 32);
			this->ctrlCreateSheet->TabIndex = 0;
			this->ctrlCreateSheet->Text = L"Create";
			this->ctrlCreateSheet->UseVisualStyleBackColor = true;
			this->ctrlCreateSheet->Click += gcnew System::EventHandler(this, &SheetForm::ctrlCreateSheet_Click);
			// 
			// ctrlSheetExtract
			// 
			this->ctrlSheetExtract->Location = System::Drawing::Point(266, 277);
			this->ctrlSheetExtract->Name = L"ctrlSheetExtract";
			this->ctrlSheetExtract->Size = System::Drawing::Size(91, 32);
			this->ctrlSheetExtract->TabIndex = 1;
			this->ctrlSheetExtract->Text = L"Extract";
			this->ctrlSheetExtract->UseVisualStyleBackColor = true;
			this->ctrlSheetExtract->Click += gcnew System::EventHandler(this, &SheetForm::ctrlSheetExtract_Click);
			// 
			// ctrlStartIndex
			// 
			this->ctrlStartIndex->Location = System::Drawing::Point(149, 80);
			this->ctrlStartIndex->Margin = System::Windows::Forms::Padding(50, 3, 30, 10);
			this->ctrlStartIndex->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000000, 0, 0, 0 });
			this->ctrlStartIndex->Name = L"ctrlStartIndex";
			this->ctrlStartIndex->Size = System::Drawing::Size(206, 20);
			this->ctrlStartIndex->TabIndex = 3;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(13, 80);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(133, 16);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Starting index (name)";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(13, 13);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(88, 16);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Source folder";
			// 
			// ctrlRekey
			// 
			this->ctrlRekey->FormattingEnabled = true;
			this->ctrlRekey->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"No", L"Yes" });
			this->ctrlRekey->Location = System::Drawing::Point(149, 113);
			this->ctrlRekey->Margin = System::Windows::Forms::Padding(50, 3, 30, 10);
			this->ctrlRekey->Name = L"ctrlRekey";
			this->ctrlRekey->Size = System::Drawing::Size(206, 21);
			this->ctrlRekey->TabIndex = 7;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(13, 114);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(80, 16);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Rekey cyan";
			// 
			// ctrlSourceFolder
			// 
			this->ctrlSourceFolder->FormattingEnabled = true;
			this->ctrlSourceFolder->Location = System::Drawing::Point(149, 12);
			this->ctrlSourceFolder->Margin = System::Windows::Forms::Padding(50, 3, 30, 10);
			this->ctrlSourceFolder->Name = L"ctrlSourceFolder";
			this->ctrlSourceFolder->Size = System::Drawing::Size(206, 21);
			this->ctrlSourceFolder->TabIndex = 9;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(13, 46);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(83, 16);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Output folder";
			// 
			// ctrlOutputFolder
			// 
			this->ctrlOutputFolder->FormattingEnabled = true;
			this->ctrlOutputFolder->Location = System::Drawing::Point(149, 46);
			this->ctrlOutputFolder->Margin = System::Windows::Forms::Padding(50, 3, 30, 10);
			this->ctrlOutputFolder->Name = L"ctrlOutputFolder";
			this->ctrlOutputFolder->Size = System::Drawing::Size(206, 21);
			this->ctrlOutputFolder->TabIndex = 11;
			// 
			// ctrlOpenFolder
			// 
			this->ctrlOpenFolder->Location = System::Drawing::Point(81, 277);
			this->ctrlOpenFolder->Name = L"ctrlOpenFolder";
			this->ctrlOpenFolder->Size = System::Drawing::Size(82, 32);
			this->ctrlOpenFolder->TabIndex = 12;
			this->ctrlOpenFolder->Text = L"Open Folder";
			this->ctrlOpenFolder->UseVisualStyleBackColor = true;
			this->ctrlOpenFolder->Click += gcnew System::EventHandler(this, &SheetForm::ctrlOpenFolder_Click);
			// 
			// chbExtractBetweenRange
			// 
			this->chbExtractBetweenRange->AutoSize = true;
			this->chbExtractBetweenRange->Location = System::Drawing::Point(16, 147);
			this->chbExtractBetweenRange->Name = L"chbExtractBetweenRange";
			this->chbExtractBetweenRange->Size = System::Drawing::Size(133, 17);
			this->chbExtractBetweenRange->TabIndex = 13;
			this->chbExtractBetweenRange->Text = L"Extract between range";
			this->chbExtractBetweenRange->UseVisualStyleBackColor = true;
			this->chbExtractBetweenRange->CheckedChanged += gcnew System::EventHandler(this, &SheetForm::chbExtractBetweenRange_CheckedChanged);
			// 
			// ctrlExtractBetweenRange1
			// 
			this->ctrlExtractBetweenRange1->Enabled = false;
			this->ctrlExtractBetweenRange1->Location = System::Drawing::Point(16, 170);
			this->ctrlExtractBetweenRange1->Margin = System::Windows::Forms::Padding(50, 3, 30, 10);
			this->ctrlExtractBetweenRange1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000000, 0, 0, 0 });
			this->ctrlExtractBetweenRange1->Name = L"ctrlExtractBetweenRange1";
			this->ctrlExtractBetweenRange1->Size = System::Drawing::Size(147, 20);
			this->ctrlExtractBetweenRange1->TabIndex = 14;
			// 
			// ctrlExtractBetweenRange2
			// 
			this->ctrlExtractBetweenRange2->Enabled = false;
			this->ctrlExtractBetweenRange2->Location = System::Drawing::Point(210, 170);
			this->ctrlExtractBetweenRange2->Margin = System::Windows::Forms::Padding(50, 3, 30, 10);
			this->ctrlExtractBetweenRange2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000000, 0, 0, 0 });
			this->ctrlExtractBetweenRange2->Name = L"ctrlExtractBetweenRange2";
			this->ctrlExtractBetweenRange2->Size = System::Drawing::Size(147, 20);
			this->ctrlExtractBetweenRange2->TabIndex = 15;
			// 
			// chbExtractFromIndex
			// 
			this->chbExtractFromIndex->AutoSize = true;
			this->chbExtractFromIndex->Location = System::Drawing::Point(16, 203);
			this->chbExtractFromIndex->Name = L"chbExtractFromIndex";
			this->chbExtractFromIndex->Size = System::Drawing::Size(147, 17);
			this->chbExtractFromIndex->TabIndex = 16;
			this->chbExtractFromIndex->Text = L"Extract starting from index";
			this->chbExtractFromIndex->UseVisualStyleBackColor = true;
			this->chbExtractFromIndex->CheckedChanged += gcnew System::EventHandler(this, &SheetForm::chbExtractFromIndex_CheckedChanged);
			// 
			// ctrlExtractFromIndex
			// 
			this->ctrlExtractFromIndex->Enabled = false;
			this->ctrlExtractFromIndex->Location = System::Drawing::Point(16, 226);
			this->ctrlExtractFromIndex->Margin = System::Windows::Forms::Padding(50, 3, 30, 10);
			this->ctrlExtractFromIndex->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000000, 0, 0, 0 });
			this->ctrlExtractFromIndex->Name = L"ctrlExtractFromIndex";
			this->ctrlExtractFromIndex->Size = System::Drawing::Size(147, 20);
			this->ctrlExtractFromIndex->TabIndex = 17;
			// 
			// SheetForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(367, 321);
			this->Controls->Add(this->ctrlExtractFromIndex);
			this->Controls->Add(this->chbExtractFromIndex);
			this->Controls->Add(this->ctrlExtractBetweenRange2);
			this->Controls->Add(this->ctrlExtractBetweenRange1);
			this->Controls->Add(this->chbExtractBetweenRange);
			this->Controls->Add(this->ctrlOpenFolder);
			this->Controls->Add(this->ctrlOutputFolder);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->ctrlSourceFolder);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->ctrlRekey);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ctrlStartIndex);
			this->Controls->Add(this->ctrlSheetExtract);
			this->Controls->Add(this->ctrlCreateSheet);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(383, 360);
			this->MinimumSize = System::Drawing::Size(383, 360);
			this->Name = L"SheetForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sprite Sheet Manager";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &SheetForm::SheetForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &SheetForm::SheetForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlStartIndex))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlExtractBetweenRange1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlExtractBetweenRange2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlExtractFromIndex))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void SheetForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
private: System::Void SheetForm_Load(System::Object^  sender, System::EventArgs^  e);
private: System::Void ctrlCreateSheet_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ctrlSheetExtract_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ctrlOpenFolder_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void chbExtractBetweenRange_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void chbExtractFromIndex_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
};
}
