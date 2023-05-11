#pragma once

namespace BanduraCursovaPencil {

	//using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing;
	using namespace System::Data::SqlServerCe;

	/// <summary>
	/// Summary for EditPencil
	/// </summary>
	public ref class EditPencil : public System::Windows::Forms::Form
	{
		System::Data::SqlServerCe::SqlCeConnection^ connect;
		int PencilId;
		int LeadId;
		int TypeId;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::ComboBox^ comboBox3;
		   int DistributorId;
	public:
		EditPencil(int temp, int Typeid, int Leadid, int Distributorid)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			SqlCeEngine^ dbEngine = gcnew SqlCeEngine();
			dbEngine->LocalConnectionString = "Data Source=PencilDB.sdf;";
			connect = gcnew SqlCeConnection("Data Source=PencilDB.sdf;");
			this->PencilId = -1;
			this->TypeId = Typeid;
			this->LeadId = Leadid;
			this->DistributorId = Distributorid;
			textBox1->Text = "";

			addItemsComboBox1();
			addItemsComboBox2();


			connect->Open();
			SqlCeCommand^ command3 = connect->CreateCommand();
			command3->CommandText = "SELECT Name FROM Distributor";
			SqlCeDataReader^ sqlRead3 = command3->ExecuteReader();
			while (sqlRead3->Read()) {
				comboBox3->Items->Add(System::Convert::ToString(sqlRead3["Name"]));
			}
			connect->Close();
			sqlRead3->Close();

		}
		EditPencil(int pId) {
			InitializeComponent();
			SqlCeEngine^ dbEngine = gcnew SqlCeEngine();
			dbEngine->LocalConnectionString = "Data Source=PencilDB.sdf;";
			connect = gcnew SqlCeConnection("Data Source=PencilDB.sdf;");

			addItemsComboBox1();
			addItemsComboBox2();

			connect->Open();
			SqlCeCommand^ command3 = connect->CreateCommand();
			command3->CommandText = "SELECT Name FROM Distributor";
			SqlCeDataReader^ sqlRead3 = command3->ExecuteReader();
			while (sqlRead3->Read()) {
				comboBox3->Items->Add(System::Convert::ToString(sqlRead3["Name"]));
			}
			connect->Close();
			sqlRead3->Close();
			this->PencilId = pId;
			int Type;
			int Lead;
			int Distributor;
			connect->Open();
			SqlCeCommand^ command4 = connect->CreateCommand();
			command4->CommandText = "SELECT * FROM [Pencil] WHERE [Id]=@pId";
			command4->Parameters->AddWithValue("@pId", pId);
			SqlCeDataReader^ sqlRead4 = command4->ExecuteReader();
			while (sqlRead4->Read()) {
				textBox1->Text = System::Convert::ToString(sqlRead4["Name"]);
				Distributor = System::Convert::ToInt32(sqlRead4["id_Distributor"]);
				Lead = System::Convert::ToInt32(sqlRead4["id_Lead"]);
				Type = System::Convert::ToInt32(sqlRead4["id_Type"]);
			}
			connect->Close();
			sqlRead4->Close();
			this->currComboBox1Set(Lead);
			this->currComboBox2Set(Type);
			this->currComboBox3Set(Distributor);
		}

		void addItemsComboBox1() { 
			System::String^ item = "";
			connect->Open();
			SqlCeCommand^ command2 = connect->CreateCommand();
			command2->CommandText = "SELECT * FROM Lead";
			SqlCeDataReader^ sqlRead2 = command2->ExecuteReader();
			while (sqlRead2->Read()) {
				item = System::Convert::ToString(sqlRead2["Thickness"]) + "," + System::Convert::ToString(sqlRead2["Color"]);
				comboBox1->Items->Add(item);
			}
			connect->Close();
			sqlRead2->Close();
		}

		void addItemsComboBox2() {
			System::String^ item = "";
			connect->Open();
			SqlCeCommand^ command2 = connect->CreateCommand();
			command2->CommandText = "SELECT * FROM Type";
			SqlCeDataReader^ sqlRead2 = command2->ExecuteReader();
			while (sqlRead2->Read()) {
				item = System::Convert::ToString(sqlRead2["type"]) + "," + System::Convert::ToString(sqlRead2["form"]) + "," + System::Convert::ToString(sqlRead2["hardness"]);
				comboBox2->Items->Add(item);
			}
			connect->Close();
			sqlRead2->Close();
		}

		void currComboBox1Set(int id)
		{
			connect->Open();
			System::String^ query = " SELECT * FROM Lead WHERE Id LIKE '" + id + "';";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				comboBox1->Text = System::Convert::ToString(sqlRead["Thickness"]) + "," + System::Convert::ToString(sqlRead["Color"]);
			}
			connect->Close();
			sqlRead->Close();
		}

		int getCurrComboBox1()
		{
			int id;
			System::String^ item = comboBox1->Text;
			cli::array<System::String^>^ splitArray = item->Split(',');
			System::String^ thickness = splitArray[0];
			System::String^ color = splitArray[1];
			connect->Open();
			System::String^ queryS = "SELECT * FROM Lead WHERE Thickness LIKE '" + thickness + "' AND Color LIKE '" + color + "';" ;
			SqlCeCommand^ commandS = connect->CreateCommand();
			commandS->CommandText = queryS;
			SqlCeDataReader^ sqlReadS = commandS->ExecuteReader();
			bool hasRow = sqlReadS->Read();
			if (hasRow) {
				id = System::Convert::ToInt32(sqlReadS["Id"]);
			}
			sqlReadS->Close();
			connect->Close();
			return id;
		}

		void currComboBox2Set(int id)
		{
			connect->Open();
			System::String^ query = " SELECT * FROM Type WHERE Id LIKE '" + id + "';";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				comboBox2->Text = System::Convert::ToString(sqlRead["type"]) + "," + System::Convert::ToString(sqlRead["form"]) + "," + System::Convert::ToString(sqlRead["hardness"]);
			}
			connect->Close();
			sqlRead->Close();
		}

		int getCurrComboBox2()
		{
			int id;
			System::String^ item = comboBox2->Text;
			cli::array<System::String^>^ splitArray = item->Split(',');
			System::String^ type = splitArray[0];
			System::String^ form = splitArray[1];
			System::String^ hardness = splitArray[2];
			connect->Open();
			System::String^ queryS = "SELECT * FROM Type WHERE type LIKE '" + type + "' AND form LIKE '" + form + "' AND hardness LIKE '" + hardness + "' ;";
			SqlCeCommand^ commandS = connect->CreateCommand();
			commandS->CommandText = queryS;
			SqlCeDataReader^ sqlReadS = commandS->ExecuteReader();
			bool hasRow = sqlReadS->Read();
			if (hasRow) {
				id = System::Convert::ToInt32(sqlReadS["Id"]);
			}
			sqlReadS->Close();
			connect->Close();
			return id;
		}

		/*
		void currComboBox1Set(int id)
		{
			connect->Open();
			System::String^ query = "SELECT Name FROM Distributor WHERE Id LIKE '" + id + "';";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				comboBox3->Text = System::Convert::ToString(sqlRead["Name"]);
			}
			connect->Close();
			sqlRead->Close();
		}


		int getCurrComboBox3()
		{
			int id;
			connect->Open();
			System::String^ queryS = "SELECT Id FROM Distributor WHERE Name LIKE '" + comboBox3->Text + "';";
			SqlCeCommand^ commandS = connect->CreateCommand();
			commandS->CommandText = queryS;
			SqlCeDataReader^ sqlReadS = commandS->ExecuteReader();
			bool hasRow = sqlReadS->Read();
			if (hasRow) {
				id = System::Convert::ToInt32(sqlReadS["Id"]);
			}
			sqlReadS->Close();
			connect->Close();
			return id;
		}
		
		void currComboBox3Set(int id)
		{
			connect->Open();
			System::String^ query = "SELECT Name FROM Distributor WHERE Id LIKE '" + id + "';";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				comboBox3->Text = System::Convert::ToString(sqlRead["Name"]);
			}
			connect->Close();
			sqlRead->Close();
		}


		int getCurrComboBox3()
		{
			int id;
			connect->Open();
			System::String^ queryS = "SELECT Id FROM Distributor WHERE Name LIKE '" + comboBox3->Text + "';";
			SqlCeCommand^ commandS = connect->CreateCommand();
			commandS->CommandText = queryS;
			SqlCeDataReader^ sqlReadS = commandS->ExecuteReader();
			bool hasRow = sqlReadS->Read();
			if (hasRow) {
				id = System::Convert::ToInt32(sqlReadS["Id"]);
			}
			sqlReadS->Close();
			connect->Close();
			return id;
		}
		*/
		void currComboBox3Set(int id)
		{
			connect->Open();
			System::String^ query = "SELECT Name FROM Distributor WHERE Id LIKE '" + id + "';";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				comboBox3->Text = System::Convert::ToString(sqlRead["Name"]);
			}
			connect->Close();
			sqlRead->Close();
		}


		int getCurrComboBox3()
		{
			int id;
			connect->Open();
			System::String^ queryS = "SELECT Id FROM Distributor WHERE Name LIKE '" + comboBox3->Text + "';";
			SqlCeCommand^ commandS = connect->CreateCommand();
			commandS->CommandText = queryS;
			SqlCeDataReader^ sqlReadS = commandS->ExecuteReader();
			bool hasRow = sqlReadS->Read();
			if (hasRow) {
				id = System::Convert::ToInt32(sqlReadS["Id"]);
			}
			sqlReadS->Close();
			connect->Close();
			return id;
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EditPencil()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::ComboBox^ comboBox1;

	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;

	private: System::Windows::Forms::Label^ label4;

	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(229, 59);
			this->comboBox1->Margin = System::Windows::Forms::Padding(2);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(275, 25);
			this->comboBox1->TabIndex = 84;
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(304, 186);
			this->button2->Margin = System::Windows::Forms::Padding(2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(158, 51);
			this->button2->TabIndex = 82;
			this->button2->Text = L"Відміна";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &EditPencil::button2_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(13, 186);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(158, 51);
			this->button1->TabIndex = 81;
			this->button1->Text = L"Зберегти";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &EditPencil::button1_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(9, 58);
			this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(179, 24);
			this->label4->TabIndex = 79;
			this->label4->Text = L"Стержень олівця";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(229, 13);
			this->textBox1->Margin = System::Windows::Forms::Padding(2);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(275, 28);
			this->textBox1->TabIndex = 77;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label2->Location = System::Drawing::Point(9, 17);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(138, 24);
			this->label2->TabIndex = 76;
			this->label2->Text = L"Назва олівця";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(9, 106);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(116, 24);
			this->label1->TabIndex = 86;
			this->label1->Text = L"Тип олівця";
			// 
			// comboBox2
			// 
			this->comboBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(229, 105);
			this->comboBox2->Margin = System::Windows::Forms::Padding(2);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(275, 25);
			this->comboBox2->TabIndex = 87;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(9, 147);
			this->label5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(105, 24);
			this->label5->TabIndex = 88;
			this->label5->Text = L"Виробник";
			// 
			// comboBox3
			// 
			this->comboBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Location = System::Drawing::Point(229, 146);
			this->comboBox3->Margin = System::Windows::Forms::Padding(2);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(275, 25);
			this->comboBox3->TabIndex = 89;
			// 
			// EditPencil
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->ClientSize = System::Drawing::Size(515, 261);
			this->Controls->Add(this->comboBox3);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"EditPencil";
			this->Text = L"Новий олівець";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void insert() {
		try {
			int lID = this->getCurrComboBox1();
			int tID = this->getCurrComboBox2();
			int dID = this->getCurrComboBox3();

			connect->Open();
			System::String^ query = "INSERT INTO [Pencil]([Name], [id_Distributor], [id_Lead], [id_Type])" +
				"VALUES('" + textBox1->Text + "', " + dID + ", " + lID + ", '" + tID + "');";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			if (command->ExecuteNonQuery() > 0) {
				MessageBox::Show("Добавлено!");
			}
			else MessageBox::Show("Введіть усі данні!");
			connect->Close();
		}
		catch (...)
		{
			MessageBox::Show("Дані введено не правильно");
		}
	}
	private: void update() {
		try {
			int lID = this->getCurrComboBox1();
			int tID = this->getCurrComboBox2();
			int dID = this->getCurrComboBox3();
			connect->Open();
			System::String^ query = "UPDATE [Pencil] SET [Name]='" + textBox1->Text + "', [id_Distributor]=" + dID + ", [id_Lead]=" + lID + ", [id_Type]='" + tID + "' WHERE [Id]=" + this->PencilId + ";";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			if (command->ExecuteNonQuery() == 0) {
				MessageBox::Show("Оновлено!");
			}
			connect->Close();
		}
		catch (...)
		{
			MessageBox::Show("Дані введено не правильно");
		}
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBox1->Text->Length != 0 && comboBox1->Text->Length != 0 && comboBox2->Text->Length != 0 && comboBox3->Text->Length != 0) {
			if (this->PencilId == -1) insert();
			else update();
			this->Close();
		}
		else {
			MessageBox::Show("Введіть більше даних");
		}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	};
}
