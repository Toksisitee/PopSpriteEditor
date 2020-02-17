#pragma once

namespace PopSpriteEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::ListView^  ctrlListSprites;
	protected:
	private: System::Windows::Forms::ColumnHeader^  HIndex;
	public:
	private: System::Windows::Forms::ColumnHeader^  HOffset;
	private: System::Windows::Forms::ColumnHeader^  HHeight;
	private: System::Windows::Forms::ColumnHeader^  HWidth;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  createSpriteBankToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  memoryToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  imagesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  debugDataToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem1;
	private: System::Windows::Forms::GroupBox^  ctrlGroupBoxSelect;
	private: System::Windows::Forms::Label^  ctrlSpriteDataMatching;
	private: System::Windows::Forms::Label^  ctrlSpriteDataBMPLength;
	private: System::Windows::Forms::Label^  ctrlSpriteDataLength;
	public: System::Windows::Forms::RichTextBox^  ctrlHexBMPView;
	private:

	public:

	public: System::Windows::Forms::RichTextBox^  ctrlHexView;
	private:

	public:


	private: System::Windows::Forms::Button^  ctrlButtonSaveSprite;

	private: System::Windows::Forms::TrackBar^  ctrlSpriteSize;
	private: System::Windows::Forms::NumericUpDown^  ctrlNumericGoto;
	private: System::Windows::Forms::PictureBox^  ctrlSpriteImg;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::PictureBox^  ctrlSpriteImg2;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::PictureBox^  ctrlPaletteImg;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ToolStripMenuItem^  dumpSpritesToolStripMenuItem;
	private: System::Windows::Forms::ContextMenuStrip^  ctrlListSpritesContext;
	private: System::Windows::Forms::ToolStripMenuItem^  CopyOffset;
	private: System::Windows::Forms::ToolStripMenuItem^  colorKeyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox1;



	private: System::ComponentModel::IContainer^  components;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->ctrlListSprites = (gcnew System::Windows::Forms::ListView());
			this->HIndex = (gcnew System::Windows::Forms::ColumnHeader());
			this->HOffset = (gcnew System::Windows::Forms::ColumnHeader());
			this->HHeight = (gcnew System::Windows::Forms::ColumnHeader());
			this->HWidth = (gcnew System::Windows::Forms::ColumnHeader());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->createSpriteBankToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->memoryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->imagesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dumpSpritesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->colorKeyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripTextBox1 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->debugDataToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ctrlGroupBoxSelect = (gcnew System::Windows::Forms::GroupBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->ctrlSpriteDataMatching = (gcnew System::Windows::Forms::Label());
			this->ctrlSpriteDataBMPLength = (gcnew System::Windows::Forms::Label());
			this->ctrlSpriteDataLength = (gcnew System::Windows::Forms::Label());
			this->ctrlHexBMPView = (gcnew System::Windows::Forms::RichTextBox());
			this->ctrlHexView = (gcnew System::Windows::Forms::RichTextBox());
			this->ctrlButtonSaveSprite = (gcnew System::Windows::Forms::Button());
			this->ctrlNumericGoto = (gcnew System::Windows::Forms::NumericUpDown());
			this->ctrlSpriteSize = (gcnew System::Windows::Forms::TrackBar());
			this->ctrlSpriteImg = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->ctrlSpriteImg2 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->ctrlPaletteImg = (gcnew System::Windows::Forms::PictureBox());
			this->ctrlListSpritesContext = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->CopyOffset = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->ctrlGroupBoxSelect->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlNumericGoto))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlSpriteSize))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlSpriteImg))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlSpriteImg2))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlPaletteImg))->BeginInit();
			this->ctrlListSpritesContext->SuspendLayout();
			this->SuspendLayout();
			// 
			// ctrlListSprites
			// 
			this->ctrlListSprites->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->ctrlListSprites->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
				this->HIndex, this->HOffset,
					this->HHeight, this->HWidth
			});
			this->ctrlListSprites->FullRowSelect = true;
			this->ctrlListSprites->HideSelection = false;
			this->ctrlListSprites->Location = System::Drawing::Point(12, 27);
			this->ctrlListSprites->MultiSelect = false;
			this->ctrlListSprites->Name = L"ctrlListSprites";
			this->ctrlListSprites->Size = System::Drawing::Size(218, 634);
			this->ctrlListSprites->TabIndex = 3;
			this->ctrlListSprites->UseCompatibleStateImageBehavior = false;
			this->ctrlListSprites->View = System::Windows::Forms::View::Details;
			this->ctrlListSprites->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::ctrlListSprites_SelectedIndexChanged);
			this->ctrlListSprites->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::ctrlListSprites_MouseClick);
			// 
			// HIndex
			// 
			this->HIndex->Text = L"Index";
			this->HIndex->Width = 45;
			// 
			// HOffset
			// 
			this->HOffset->Text = L"Offset";
			// 
			// HHeight
			// 
			this->HHeight->Text = L"Height";
			this->HHeight->Width = 45;
			// 
			// HWidth
			// 
			this->HWidth->Text = L"Width";
			this->HWidth->Width = 45;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->fileToolStripMenuItem,
					this->aboutToolStripMenuItem, this->aboutToolStripMenuItem1
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(895, 24);
			this->menuStrip1->TabIndex = 4;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->openToolStripMenuItem,
					this->createSpriteBankToolStripMenuItem, this->dumpSpritesToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(170, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openToolStripMenuItem_Click);
			// 
			// createSpriteBankToolStripMenuItem
			// 
			this->createSpriteBankToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->memoryToolStripMenuItem,
					this->imagesToolStripMenuItem
			});
			this->createSpriteBankToolStripMenuItem->Name = L"createSpriteBankToolStripMenuItem";
			this->createSpriteBankToolStripMenuItem->Size = System::Drawing::Size(170, 22);
			this->createSpriteBankToolStripMenuItem->Text = L"Create Sprite Bank";
			// 
			// memoryToolStripMenuItem
			// 
			this->memoryToolStripMenuItem->Name = L"memoryToolStripMenuItem";
			this->memoryToolStripMenuItem->Size = System::Drawing::Size(150, 22);
			this->memoryToolStripMenuItem->Text = L"From Memory";
			this->memoryToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::memoryToolStripMenuItem_Click);
			// 
			// imagesToolStripMenuItem
			// 
			this->imagesToolStripMenuItem->Name = L"imagesToolStripMenuItem";
			this->imagesToolStripMenuItem->Size = System::Drawing::Size(150, 22);
			this->imagesToolStripMenuItem->Text = L"From Images";
			this->imagesToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::imagesToolStripMenuItem_Click);
			// 
			// dumpSpritesToolStripMenuItem
			// 
			this->dumpSpritesToolStripMenuItem->Name = L"dumpSpritesToolStripMenuItem";
			this->dumpSpritesToolStripMenuItem->Size = System::Drawing::Size(170, 22);
			this->dumpSpritesToolStripMenuItem->Text = L"Export Sprites";
			this->dumpSpritesToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::dumpSpritesToolStripMenuItem_Click);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->colorKeyToolStripMenuItem,
					this->debugDataToolStripMenuItem
			});
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(61, 20);
			this->aboutToolStripMenuItem->Text = L"Options";
			// 
			// colorKeyToolStripMenuItem
			// 
			this->colorKeyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripTextBox1 });
			this->colorKeyToolStripMenuItem->Name = L"colorKeyToolStripMenuItem";
			this->colorKeyToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->colorKeyToolStripMenuItem->Text = L"Color Key";
			// 
			// toolStripTextBox1
			// 
			this->toolStripTextBox1->Name = L"toolStripTextBox1";
			this->toolStripTextBox1->ShortcutsEnabled = false;
			this->toolStripTextBox1->Size = System::Drawing::Size(100, 23);
			this->toolStripTextBox1->Text = L"255";
			this->toolStripTextBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::toolStripTextBox1_KeyPress);
			this->toolStripTextBox1->TextChanged += gcnew System::EventHandler(this, &MainForm::toolStripTextBox1_TextChanged);
			// 
			// debugDataToolStripMenuItem
			// 
			this->debugDataToolStripMenuItem->CheckOnClick = true;
			this->debugDataToolStripMenuItem->Name = L"debugDataToolStripMenuItem";
			this->debugDataToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->debugDataToolStripMenuItem->Text = L"Debug";
			this->debugDataToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &MainForm::debugDataToolStripMenuItem_CheckedChanged);
			// 
			// aboutToolStripMenuItem1
			// 
			this->aboutToolStripMenuItem1->Name = L"aboutToolStripMenuItem1";
			this->aboutToolStripMenuItem1->Size = System::Drawing::Size(52, 20);
			this->aboutToolStripMenuItem1->Text = L"About";
			this->aboutToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainForm::aboutToolStripMenuItem1_Click);
			// 
			// ctrlGroupBoxSelect
			// 
			this->ctrlGroupBoxSelect->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->ctrlGroupBoxSelect->Controls->Add(this->label2);
			this->ctrlGroupBoxSelect->Controls->Add(this->ctrlSpriteDataMatching);
			this->ctrlGroupBoxSelect->Controls->Add(this->ctrlSpriteDataBMPLength);
			this->ctrlGroupBoxSelect->Controls->Add(this->ctrlSpriteDataLength);
			this->ctrlGroupBoxSelect->Controls->Add(this->ctrlHexBMPView);
			this->ctrlGroupBoxSelect->Controls->Add(this->ctrlHexView);
			this->ctrlGroupBoxSelect->Controls->Add(this->ctrlButtonSaveSprite);
			this->ctrlGroupBoxSelect->Controls->Add(this->ctrlNumericGoto);
			this->ctrlGroupBoxSelect->Controls->Add(this->ctrlSpriteSize);
			this->ctrlGroupBoxSelect->Controls->Add(this->ctrlSpriteImg);
			this->ctrlGroupBoxSelect->Location = System::Drawing::Point(236, 27);
			this->ctrlGroupBoxSelect->Name = L"ctrlGroupBoxSelect";
			this->ctrlGroupBoxSelect->Size = System::Drawing::Size(345, 634);
			this->ctrlGroupBoxSelect->TabIndex = 6;
			this->ctrlGroupBoxSelect->TabStop = false;
			this->ctrlGroupBoxSelect->Text = L"Sprite: #0";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(92, 16);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(40, 13);
			this->label2->TabIndex = 16;
			this->label2->Text = L"Select:";
			// 
			// ctrlSpriteDataMatching
			// 
			this->ctrlSpriteDataMatching->AutoSize = true;
			this->ctrlSpriteDataMatching->BackColor = System::Drawing::SystemColors::Control;
			this->ctrlSpriteDataMatching->ForeColor = System::Drawing::SystemColors::ControlText;
			this->ctrlSpriteDataMatching->Location = System::Drawing::Point(287, 399);
			this->ctrlSpriteDataMatching->Name = L"ctrlSpriteDataMatching";
			this->ctrlSpriteDataMatching->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->ctrlSpriteDataMatching->Size = System::Drawing::Size(51, 13);
			this->ctrlSpriteDataMatching->TabIndex = 15;
			this->ctrlSpriteDataMatching->Text = L"Matching";
			// 
			// ctrlSpriteDataBMPLength
			// 
			this->ctrlSpriteDataBMPLength->AutoSize = true;
			this->ctrlSpriteDataBMPLength->Location = System::Drawing::Point(6, 399);
			this->ctrlSpriteDataBMPLength->Name = L"ctrlSpriteDataBMPLength";
			this->ctrlSpriteDataBMPLength->Size = System::Drawing::Size(168, 13);
			this->ctrlSpriteDataBMPLength->TabIndex = 14;
			this->ctrlSpriteDataBMPLength->Text = L"BMP Data (conversion). Length: 0";
			// 
			// ctrlSpriteDataLength
			// 
			this->ctrlSpriteDataLength->AutoSize = true;
			this->ctrlSpriteDataLength->Location = System::Drawing::Point(6, 514);
			this->ctrlSpriteDataLength->Name = L"ctrlSpriteDataLength";
			this->ctrlSpriteDataLength->Size = System::Drawing::Size(121, 13);
			this->ctrlSpriteDataLength->TabIndex = 12;
			this->ctrlSpriteDataLength->Text = L"Memory Data. Length: 0";
			// 
			// ctrlHexBMPView
			// 
			this->ctrlHexBMPView->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->ctrlHexBMPView->DetectUrls = false;
			this->ctrlHexBMPView->Enabled = false;
			this->ctrlHexBMPView->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ctrlHexBMPView->Location = System::Drawing::Point(6, 415);
			this->ctrlHexBMPView->Name = L"ctrlHexBMPView";
			this->ctrlHexBMPView->Size = System::Drawing::Size(332, 98);
			this->ctrlHexBMPView->TabIndex = 13;
			this->ctrlHexBMPView->Text = L"";
			// 
			// ctrlHexView
			// 
			this->ctrlHexView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->ctrlHexView->DetectUrls = false;
			this->ctrlHexView->Enabled = false;
			this->ctrlHexView->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ctrlHexView->Location = System::Drawing::Point(5, 530);
			this->ctrlHexView->Name = L"ctrlHexView";
			this->ctrlHexView->Size = System::Drawing::Size(333, 98);
			this->ctrlHexView->TabIndex = 11;
			this->ctrlHexView->Text = L"";
			// 
			// ctrlButtonSaveSprite
			// 
			this->ctrlButtonSaveSprite->Location = System::Drawing::Point(91, 40);
			this->ctrlButtonSaveSprite->Name = L"ctrlButtonSaveSprite";
			this->ctrlButtonSaveSprite->Size = System::Drawing::Size(120, 23);
			this->ctrlButtonSaveSprite->TabIndex = 5;
			this->ctrlButtonSaveSprite->Text = L"Save Sprite";
			this->ctrlButtonSaveSprite->UseVisualStyleBackColor = true;
			this->ctrlButtonSaveSprite->Click += gcnew System::EventHandler(this, &MainForm::ctrlButtonSaveSprite_Click);
			// 
			// ctrlNumericGoto
			// 
			this->ctrlNumericGoto->Location = System::Drawing::Point(138, 14);
			this->ctrlNumericGoto->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->ctrlNumericGoto->Name = L"ctrlNumericGoto";
			this->ctrlNumericGoto->Size = System::Drawing::Size(73, 20);
			this->ctrlNumericGoto->TabIndex = 2;
			this->ctrlNumericGoto->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::ctrlNumericGoto_KeyDown);
			// 
			// ctrlSpriteSize
			// 
			this->ctrlSpriteSize->Location = System::Drawing::Point(5, 102);
			this->ctrlSpriteSize->Minimum = 1;
			this->ctrlSpriteSize->Name = L"ctrlSpriteSize";
			this->ctrlSpriteSize->Size = System::Drawing::Size(122, 45);
			this->ctrlSpriteSize->TabIndex = 3;
			this->ctrlSpriteSize->Value = 1;
			this->ctrlSpriteSize->ValueChanged += gcnew System::EventHandler(this, &MainForm::ctrlSpriteSize_ValueChanged);
			// 
			// ctrlSpriteImg
			// 
			this->ctrlSpriteImg->Location = System::Drawing::Point(6, 16);
			this->ctrlSpriteImg->Name = L"ctrlSpriteImg";
			this->ctrlSpriteImg->Size = System::Drawing::Size(80, 80);
			this->ctrlSpriteImg->TabIndex = 1;
			this->ctrlSpriteImg->TabStop = false;
			this->ctrlSpriteImg->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::ctrlSpriteImg_Paint);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->AutoSize = true;
			this->groupBox1->Controls->Add(this->ctrlSpriteImg2);
			this->groupBox1->Location = System::Drawing::Point(587, 27);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(296, 431);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Preview";
			// 
			// ctrlSpriteImg2
			// 
			this->ctrlSpriteImg2->Location = System::Drawing::Point(6, 19);
			this->ctrlSpriteImg2->Name = L"ctrlSpriteImg2";
			this->ctrlSpriteImg2->Size = System::Drawing::Size(284, 393);
			this->ctrlSpriteImg2->TabIndex = 0;
			this->ctrlSpriteImg2->TabStop = false;
			this->ctrlSpriteImg2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::ctrlSpriteImg2_Paint);
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->Controls->Add(this->ctrlPaletteImg);
			this->groupBox2->Location = System::Drawing::Point(587, 477);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(290, 184);
			this->groupBox2->TabIndex = 8;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Palette";
			// 
			// ctrlPaletteImg
			// 
			this->ctrlPaletteImg->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->ctrlPaletteImg->Location = System::Drawing::Point(6, 19);
			this->ctrlPaletteImg->Name = L"ctrlPaletteImg";
			this->ctrlPaletteImg->Size = System::Drawing::Size(284, 159);
			this->ctrlPaletteImg->TabIndex = 6;
			this->ctrlPaletteImg->TabStop = false;
			this->ctrlPaletteImg->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::ctrlPaletteImg_Paint);
			// 
			// ctrlListSpritesContext
			// 
			this->ctrlListSpritesContext->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->CopyOffset });
			this->ctrlListSpritesContext->Name = L"ctrlListSpritesContext";
			this->ctrlListSpritesContext->Size = System::Drawing::Size(138, 26);
			// 
			// CopyOffset
			// 
			this->CopyOffset->Name = L"CopyOffset";
			this->CopyOffset->Size = System::Drawing::Size(137, 22);
			this->CopyOffset->Text = L"Copy Offset";
			this->CopyOffset->Click += gcnew System::EventHandler(this, &MainForm::CopyOffset_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(895, 663);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->ctrlGroupBoxSelect);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->ctrlListSprites);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(911, 39);
			this->Name = L"MainForm";
			this->Text = L"PopSpriteEditor";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ctrlGroupBoxSelect->ResumeLayout(false);
			this->ctrlGroupBoxSelect->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlNumericGoto))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlSpriteSize))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlSpriteImg))->EndInit();
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlSpriteImg2))->EndInit();
			this->groupBox2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ctrlPaletteImg))->EndInit();
			this->ctrlListSpritesContext->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ctrlListSprites_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ctrlSpriteImg_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
private: System::Void ctrlSpriteImg2_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
private: System::Void ctrlPaletteImg_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e);
private: System::Void ctrlSpriteSize_ValueChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ctrlButtonSaveSprite_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void debugDataToolStripMenuItem_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void memoryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void dumpSpritesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void imagesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ctrlNumericGoto_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void aboutToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ctrlListSprites_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void CopyOffset_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void toolStripTextBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
private: System::Void toolStripTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e);
};

	ref class GlobalForms abstract sealed
	{
	public:
		static MainForm^ MainWindow;
		static Form^ AboutWindow;
	};
}
