#pragma once

namespace wowwow {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyFormWOW
	/// </summary>
	public ref class MyFormWOW : public System::Windows::Forms::Form
	{
	public:
		MyFormWOW(void)
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
		~MyFormWOW()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ DOBBY;
	protected:

	private: System::Windows::Forms::Label^ SUVAT;
	private: System::Windows::Forms::Label^ selectEQ;









	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::Button^ addeq;

	private: System::Windows::Forms::Button^ eq6;

	private: System::Windows::Forms::Button^ eq5;

	private: System::Windows::Forms::Button^ eq4;

	private: System::Windows::Forms::Button^ eq3;

	private: System::Windows::Forms::Button^ eq2;

	private: System::Windows::Forms::Button^ eq1;


	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::Label^ EnterNum;
	private: System::Windows::Forms::TextBox^ putVar2;


	private: System::Windows::Forms::TextBox^ putVar1;


	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ selectedEQ;

	private: System::Windows::Forms::Button^ calculate;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ putVar5;
	private: System::Windows::Forms::TextBox^ putVar3;
	private: System::Windows::Forms::TextBox^ putVar4;

















	protected:

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyFormWOW::typeid));
			this->DOBBY = (gcnew System::Windows::Forms::Label());
			this->SUVAT = (gcnew System::Windows::Forms::Label());
			this->selectEQ = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->addeq = (gcnew System::Windows::Forms::Button());
			this->eq6 = (gcnew System::Windows::Forms::Button());
			this->eq5 = (gcnew System::Windows::Forms::Button());
			this->eq4 = (gcnew System::Windows::Forms::Button());
			this->eq3 = (gcnew System::Windows::Forms::Button());
			this->eq2 = (gcnew System::Windows::Forms::Button());
			this->eq1 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->putVar5 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->EnterNum = (gcnew System::Windows::Forms::Label());
			this->putVar1 = (gcnew System::Windows::Forms::TextBox());
			this->putVar2 = (gcnew System::Windows::Forms::TextBox());
			this->putVar3 = (gcnew System::Windows::Forms::TextBox());
			this->putVar4 = (gcnew System::Windows::Forms::TextBox());
			this->selectedEQ = (gcnew System::Windows::Forms::Label());
			this->calculate = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// DOBBY
			// 
			this->DOBBY->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->DOBBY->BackColor = System::Drawing::Color::Transparent;
			this->DOBBY->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DOBBY->Location = System::Drawing::Point(482, 896);
			this->DOBBY->Name = L"DOBBY";
			this->DOBBY->Size = System::Drawing::Size(144, 37);
			this->DOBBY->TabIndex = 0;
			this->DOBBY->Text = L"DOBBY";
			this->DOBBY->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->DOBBY->Click += gcnew System::EventHandler(this, &MyFormWOW::label1_Click);
			// 
			// SUVAT
			// 
			this->SUVAT->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->SUVAT->BackColor = System::Drawing::Color::Transparent;
			this->SUVAT->Font = (gcnew System::Drawing::Font(L"Swis721 BdCnOul BT", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SUVAT->Location = System::Drawing::Point(433, 28);
			this->SUVAT->Name = L"SUVAT";
			this->SUVAT->Size = System::Drawing::Size(282, 78);
			this->SUVAT->TabIndex = 1;
			this->SUVAT->Text = L"..SUVAT..";
			this->SUVAT->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->SUVAT->Click += gcnew System::EventHandler(this, &MyFormWOW::label2_Click);
			// 
			// selectEQ
			// 
			this->selectEQ->AutoSize = true;
			this->selectEQ->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->selectEQ->Location = System::Drawing::Point(3, 0);
			this->selectEQ->Name = L"selectEQ";
			this->selectEQ->Size = System::Drawing::Size(240, 25);
			this->selectEQ->TabIndex = 3;
			this->selectEQ->Text = L"Please select an equation.";
			this->selectEQ->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->addeq, 0, 7);
			this->tableLayoutPanel1->Controls->Add(this->eq6, 0, 6);
			this->tableLayoutPanel1->Controls->Add(this->eq5, 0, 5);
			this->tableLayoutPanel1->Controls->Add(this->eq4, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->eq3, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->eq2, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->eq1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->selectEQ, 0, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(124, 139);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 8;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 47.76119F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 52.23881F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 72)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 79)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 77)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 77)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 74)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 76)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(270, 596);
			this->tableLayoutPanel1->TabIndex = 10;
			// 
			// addeq
			// 
			this->addeq->BackColor = System::Drawing::Color::LightCyan;
			this->addeq->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->addeq->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->addeq->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addeq->ForeColor = System::Drawing::Color::Black;
			this->addeq->Location = System::Drawing::Point(3, 522);
			this->addeq->Name = L"addeq";
			this->addeq->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->addeq->Size = System::Drawing::Size(264, 71);
			this->addeq->TabIndex = 11;
			this->addeq->Text = L"Add your equation";
			this->addeq->UseVisualStyleBackColor = false;
			// 
			// eq6
			// 
			this->eq6->BackColor = System::Drawing::Color::LightCyan;
			this->eq6->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->eq6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->eq6->Location = System::Drawing::Point(3, 448);
			this->eq6->Name = L"eq6";
			this->eq6->Size = System::Drawing::Size(264, 68);
			this->eq6->TabIndex = 11;
			this->eq6->Text = L"s = ((u+v)/2)t";
			this->eq6->UseVisualStyleBackColor = false;
			// 
			// eq5
			// 
			this->eq5->BackColor = System::Drawing::Color::LightCyan;
			this->eq5->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->eq5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->eq5->Location = System::Drawing::Point(3, 371);
			this->eq5->Name = L"eq5";
			this->eq5->Size = System::Drawing::Size(264, 71);
			this->eq5->TabIndex = 11;
			this->eq5->Text = L"s = vt - (0.5)at^2";
			this->eq5->UseVisualStyleBackColor = false;
			// 
			// eq4
			// 
			this->eq4->BackColor = System::Drawing::Color::LightCyan;
			this->eq4->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->eq4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->eq4->Location = System::Drawing::Point(3, 294);
			this->eq4->Name = L"eq4";
			this->eq4->Size = System::Drawing::Size(264, 71);
			this->eq4->TabIndex = 11;
			this->eq4->Text = L"s = ut + (0.5)at^2";
			this->eq4->UseVisualStyleBackColor = false;
			// 
			// eq3
			// 
			this->eq3->BackColor = System::Drawing::Color::LightCyan;
			this->eq3->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->eq3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->eq3->Location = System::Drawing::Point(3, 215);
			this->eq3->Name = L"eq3";
			this->eq3->Size = System::Drawing::Size(264, 73);
			this->eq3->TabIndex = 11;
			this->eq3->Text = L"v^2 = u^2 + 2as";
			this->eq3->UseVisualStyleBackColor = false;
			// 
			// eq2
			// 
			this->eq2->BackColor = System::Drawing::Color::LightCyan;
			this->eq2->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->eq2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->eq2->Location = System::Drawing::Point(3, 143);
			this->eq2->Name = L"eq2";
			this->eq2->Size = System::Drawing::Size(264, 66);
			this->eq2->TabIndex = 11;
			this->eq2->Text = L"v = u + at";
			this->eq2->UseVisualStyleBackColor = false;
			// 
			// eq1
			// 
			this->eq1->BackColor = System::Drawing::Color::LightCyan;
			this->eq1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->eq1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->eq1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->eq1->ForeColor = System::Drawing::Color::Black;
			this->eq1->Location = System::Drawing::Point(3, 70);
			this->eq1->Name = L"eq1";
			this->eq1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->eq1->Size = System::Drawing::Size(264, 67);
			this->eq1->TabIndex = 11;
			this->eq1->Text = L"v = s / t";
			this->eq1->UseVisualStyleBackColor = false;
			this->eq1->Click += gcnew System::EventHandler(this, &MyFormWOW::button8_Click);
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->BackColor = System::Drawing::Color::MistyRose;
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				146)));
			this->tableLayoutPanel2->Controls->Add(this->label3, 1, 3);
			this->tableLayoutPanel2->Controls->Add(this->label2, 1, 4);
			this->tableLayoutPanel2->Controls->Add(this->label1, 1, 5);
			this->tableLayoutPanel2->Controls->Add(this->putVar5, 0, 5);
			this->tableLayoutPanel2->Controls->Add(this->label6, 1, 2);
			this->tableLayoutPanel2->Controls->Add(this->label5, 1, 1);
			this->tableLayoutPanel2->Controls->Add(this->EnterNum, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->putVar1, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->putVar2, 0, 2);
			this->tableLayoutPanel2->Controls->Add(this->putVar3, 0, 3);
			this->tableLayoutPanel2->Controls->Add(this->putVar4, 0, 4);
			this->tableLayoutPanel2->ForeColor = System::Drawing::Color::Black;
			this->tableLayoutPanel2->Location = System::Drawing::Point(605, 200);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 6;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 43.93064F)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 56.06936F)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 60)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 60)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 65)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 60)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(403, 353);
			this->tableLayoutPanel2->TabIndex = 14;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(260, 167);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(105, 25);
			this->label3->TabIndex = 18;
			this->label3->Text = L" Variable 3";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(260, 227);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(105, 25);
			this->label2->TabIndex = 18;
			this->label2->Text = L" Variable 4";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(260, 292);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(105, 25);
			this->label1->TabIndex = 18;
			this->label1->Text = L" Variable 5";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// putVar5
			// 
			this->putVar5->Dock = System::Windows::Forms::DockStyle::Right;
			this->putVar5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->putVar5->Location = System::Drawing::Point(36, 295);
			this->putVar5->Name = L"putVar5";
			this->putVar5->Size = System::Drawing::Size(218, 30);
			this->putVar5->TabIndex = 18;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(260, 107);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(105, 25);
			this->label6->TabIndex = 17;
			this->label6->Text = L" Variable 2";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(260, 47);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(105, 25);
			this->label5->TabIndex = 16;
			this->label5->Text = L" Variable 1";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label5->Click += gcnew System::EventHandler(this, &MyFormWOW::label5_Click);
			// 
			// EnterNum
			// 
			this->EnterNum->AutoSize = true;
			this->EnterNum->BackColor = System::Drawing::Color::Transparent;
			this->EnterNum->Dock = System::Windows::Forms::DockStyle::Right;
			this->EnterNum->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->EnterNum->Location = System::Drawing::Point(41, 0);
			this->EnterNum->Name = L"EnterNum";
			this->EnterNum->Size = System::Drawing::Size(213, 47);
			this->EnterNum->TabIndex = 15;
			this->EnterNum->Text = L"Please enter a number.";
			this->EnterNum->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->EnterNum->Click += gcnew System::EventHandler(this, &MyFormWOW::label4_Click);
			// 
			// putVar1
			// 
			this->putVar1->Dock = System::Windows::Forms::DockStyle::Right;
			this->putVar1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->putVar1->Location = System::Drawing::Point(36, 50);
			this->putVar1->Name = L"putVar1";
			this->putVar1->Size = System::Drawing::Size(218, 30);
			this->putVar1->TabIndex = 16;
			// 
			// putVar2
			// 
			this->putVar2->Dock = System::Windows::Forms::DockStyle::Right;
			this->putVar2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->putVar2->Location = System::Drawing::Point(36, 110);
			this->putVar2->Name = L"putVar2";
			this->putVar2->Size = System::Drawing::Size(218, 30);
			this->putVar2->TabIndex = 17;
			// 
			// putVar3
			// 
			this->putVar3->Dock = System::Windows::Forms::DockStyle::Right;
			this->putVar3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->putVar3->Location = System::Drawing::Point(36, 170);
			this->putVar3->Name = L"putVar3";
			this->putVar3->Size = System::Drawing::Size(218, 30);
			this->putVar3->TabIndex = 19;
			// 
			// putVar4
			// 
			this->putVar4->Dock = System::Windows::Forms::DockStyle::Right;
			this->putVar4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->putVar4->Location = System::Drawing::Point(36, 230);
			this->putVar4->Name = L"putVar4";
			this->putVar4->Size = System::Drawing::Size(218, 30);
			this->putVar4->TabIndex = 20;
			// 
			// selectedEQ
			// 
			this->selectedEQ->AutoSize = true;
			this->selectedEQ->BackColor = System::Drawing::Color::MistyRose;
			this->selectedEQ->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->selectedEQ->ForeColor = System::Drawing::SystemColors::ControlText;
			this->selectedEQ->Location = System::Drawing::Point(721, 139);
			this->selectedEQ->Name = L"selectedEQ";
			this->selectedEQ->Size = System::Drawing::Size(172, 29);
			this->selectedEQ->TabIndex = 16;
			this->selectedEQ->Text = L"Selected equation";
			this->selectedEQ->UseCompatibleTextRendering = true;
			this->selectedEQ->Click += gcnew System::EventHandler(this, &MyFormWOW::selectedEQ_Click);
			// 
			// calculate
			// 
			this->calculate->BackColor = System::Drawing::Color::MistyRose;
			this->calculate->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->calculate->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->calculate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->calculate->ForeColor = System::Drawing::Color::Black;
			this->calculate->Location = System::Drawing::Point(721, 578);
			this->calculate->Name = L"calculate";
			this->calculate->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->calculate->Size = System::Drawing::Size(151, 48);
			this->calculate->TabIndex = 17;
			this->calculate->Text = L"Calculate";
			this->calculate->UseVisualStyleBackColor = false;
			// 
			// MyFormWOW
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LightBlue;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(1082, 943);
			this->Controls->Add(this->calculate);
			this->Controls->Add(this->selectedEQ);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Controls->Add(this->SUVAT);
			this->Controls->Add(this->DOBBY);
			this->Controls->Add(this->tableLayoutPanel1);
			this->MinimumSize = System::Drawing::Size(1100, 990);
			this->Name = L"MyFormWOW";
			this->Text = L"MyFormWOW";
			this->Load += gcnew System::EventHandler(this, &MyFormWOW::MyFormWOW_Load);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button1_Click_2(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void MyFormWOW_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void selectedEQ_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
