#pragma once
#include "EditPencil.h"
#include "Pencil.h"
#include <stdlib.h>


namespace BanduraCursovaPencil {

	//using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlServerCe;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for PencilForm
	/// </summary>
	public ref class PencilForm : public System::Windows::Forms::Form
	{
	private: List<Pencil^>^ PencilList;
		   SqlCeConnection^ connect;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column6;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column7;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column8;
		   int LeadId;
		   int TypeId;
	private: System::Windows::Forms::ComboBox^ comboBox3;
	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label2;
		   int DistributorId;
	public:
		PencilForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			SqlCeEngine^ dbEngine = gcnew SqlCeEngine();
			dbEngine->LocalConnectionString = "Data Source=PencilDB.sdf";
			connect = gcnew SqlCeConnection(dbEngine->LocalConnectionString);
			PencilList = gcnew List<Pencil^>();
		}

		void getPencil()
		{
			this->DistributorId = getSelectedDistributorIndex();
			if (this->DistributorId < 0)
			{
				connect->Open();
				SqlCeCommand^ command = connect->CreateCommand();
				command->CommandText = "SELECT * FROM [Pencil]";
				command->Parameters->AddWithValue("@Distributor", this->DistributorId);
				SqlCeDataReader^ sqlRead = command->ExecuteReader();
				PencilList->Clear();
				while (sqlRead->Read()) {
					PencilList->Add(gcnew Pencil(
						System::Convert::ToString(sqlRead["Name"]),
						System::Convert::ToInt32(sqlRead["id_Distributor"]),
						System::Convert::ToInt32(sqlRead["id_Lead"]),
						System::Convert::ToInt32(sqlRead["id_Type"]),
						System::Convert::ToInt32(sqlRead["Id"])
					));
				}
				sqlRead->Close();
				connect->Close();
				this->updateTable();
			}
			else {
				connect->Open();
				SqlCeCommand^ command = connect->CreateCommand();
				command->CommandText = "SELECT * FROM Pencil WHERE [id_Distributor]=@Distributor";

				command->Parameters->AddWithValue(
					"@Distributor",
					this->DistributorId
				);
				SqlCeDataReader^ sqlRead = command->ExecuteReader();
				PencilList->Clear();
				while (sqlRead->Read()) {
					PencilList->Add(gcnew Pencil(
						System::Convert::ToString(sqlRead["Name"]),
						System::Convert::ToInt32(sqlRead["id_Distributor"]),
						System::Convert::ToInt32(sqlRead["id_Lead"]),
						System::Convert::ToInt32(sqlRead["id_Type"]),
						System::Convert::ToInt32(sqlRead["Id"])
					));
				}
				connect->Close();
				this->updateTable();
			}
		}

		int getSelectedDistributorIndex()
		{
			connect->Close();
			connect->Open();
			System::String^ query = "SELECT Id FROM Distributor WHERE Name LIKE '" + comboBox1->Text + "';";

			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			int result = -1;
			bool hasRow = sqlRead->Read();
			if (hasRow)
			{
				result = System::Convert::ToInt32(sqlRead["Id"]);
			}
			connect->Close();
			sqlRead->Close();
			return result;
		}

		//метод передачі запиту до БД на виконання
		void execute(System::String^ query) {
			connect->Open();
			SqlCeCommand^ command = gcnew SqlCeCommand(query, connect);
			command->ExecuteNonQuery();
			connect->Close();
		}

		// метод повернення результатів виконання запиту
		void getQueryPencil(System::String^ query) {
			connect->Open();
			SqlCeCommand^ command = gcnew SqlCeCommand(query, connect);
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			PencilList->Clear();
			while (sqlRead->Read()) {
				PencilList->Add(gcnew Pencil(
					System::Convert::ToString(sqlRead["Name"]),
					System::Convert::ToInt32(sqlRead["id_Distributor"]),
					System::Convert::ToInt32(sqlRead["id_Lead"]),
					System::Convert::ToInt32(sqlRead["id_Type"]),
					System::Convert::ToInt32(sqlRead["Id"])
				));
			}
			sqlRead->Close();
			connect->Close();
			this->updateTable();
		}
		//
		System::String^ getDistributor(int id)
		{
			connect->Open();
			System::String^ query = "SELECT Name FROM Distributor WHERE Id LIKE '" + id + "';";

			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			System::String^ result;
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				result = System::Convert::ToString(sqlRead["Name"]);
			}
			connect->Close();
			sqlRead->Close();
			return result;
		}

		System::String^ getLeadThickness(int id)
		{
			connect->Open();
			System::String^ query = "SELECT Thickness FROM Lead WHERE Id LIKE '" + id + "';";

			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			System::String^ result;
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				result = System::Convert::ToString(sqlRead["Thickness"]);
			}
			connect->Close();
			sqlRead->Close();
			return result;
		}

		System::String^ getLeadColor(int id)
		{
			connect->Open();
			System::String^ query = "SELECT Color FROM Lead WHERE Id LIKE '" + id + "';";

			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			System::String^ result;
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				result = System::Convert::ToString(sqlRead["Color"]);
			}
			connect->Close();
			sqlRead->Close();
			return result;
		}

		System::String^ getTypeType(int id)
		{
			connect->Open();
			System::String^ query = "SELECT type FROM Type WHERE Id LIKE '" + id + "';";

			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			System::String^ result;
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				result = System::Convert::ToString(sqlRead["type"]);
			}
			connect->Close();
			sqlRead->Close();
			return result;
		}

		System::String^ getTypeForm(int id)
		{
			connect->Open();
			System::String^ query = "SELECT form FROM Type WHERE Id LIKE '" + id + "';";

			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			System::String^ result;
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				result = System::Convert::ToString(sqlRead["form"]);
			}
			connect->Close();
			sqlRead->Close();
			return result;
		}

		System::String^ getTypeHardness(int id)
		{
			connect->Open();
			System::String^ query = "SELECT hardness FROM Type WHERE Id LIKE '" + id + "';";

			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			System::String^ result;
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				result = System::Convert::ToString(sqlRead["hardness"]);
			}
			connect->Close();
			sqlRead->Close();
			return result;
		}

		void updateTable() {
			int i = 0;
			dataGridView1->Rows->Clear();
			for each (Pencil ^ Pencils in PencilList) {
				this->dataGridView1->Rows->Add();
				this->dataGridView1->Rows[i]->Cells[0]->Value = Pencils->getId();
				this->dataGridView1->Rows[i]->Cells[1]->Value = Pencils->getName();
				this->dataGridView1->Rows[i]->Cells[2]->Value = this->getDistributor(Pencils->getIDDistributor());
				this->dataGridView1->Rows[i]->Cells[3]->Value = this->getLeadThickness(Pencils->getIDLead());
				this->dataGridView1->Rows[i]->Cells[4]->Value = this->getLeadColor(Pencils->getIDLead());
				this->dataGridView1->Rows[i]->Cells[5]->Value = this->getTypeType(Pencils->getIDType());
				this->dataGridView1->Rows[i]->Cells[6]->Value = this->getTypeForm(Pencils->getIDType());
				this->dataGridView1->Rows[i]->Cells[7]->Value = this->getTypeHardness(Pencils->getIDType());
				++i;
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PencilForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^ groupBox1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label3;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ comboBox1;


	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;













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
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->groupBox1->Controls->Add(this->comboBox3);
			this->groupBox1->Controls->Add(this->comboBox2);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Controls->Add(this->button4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox1->Location = System::Drawing::Point(1075, 10);
			this->groupBox1->Margin = System::Windows::Forms::Padding(2);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(2);
			this->groupBox1->Size = System::Drawing::Size(257, 292);
			this->groupBox1->TabIndex = 39;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Пошук олівця";
			// 
			// comboBox3
			// 
			this->comboBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Location = System::Drawing::Point(142, 131);
			this->comboBox3->Margin = System::Windows::Forms::Padding(2);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(95, 28);
			this->comboBox3->TabIndex = 42;
			this->comboBox3->SelectedValueChanged += gcnew System::EventHandler(this, &PencilForm::comboBox3_SelectedValueChanged);
			// 
			// comboBox2
			// 
			this->comboBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(142, 99);
			this->comboBox2->Margin = System::Windows::Forms::Padding(2);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(95, 28);
			this->comboBox2->TabIndex = 41;
			this->comboBox2->SelectedValueChanged += gcnew System::EventHandler(this, &PencilForm::comboBox2_SelectedValueChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(20, 133);
			this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(79, 17);
			this->label4->TabIndex = 40;
			this->label4->Text = L"Тип олівця";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(20, 104);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(90, 17);
			this->label2->TabIndex = 39;
			this->label2->Text = L"Колір олівця";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(142, 69);
			this->textBox1->Margin = System::Windows::Forms::Padding(2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(95, 26);
			this->textBox1->TabIndex = 36;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &PencilForm::textBox1_TextChanged);
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button4->Location = System::Drawing::Point(27, 220);
			this->button4->Margin = System::Windows::Forms::Padding(2);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(200, 56);
			this->button4->TabIndex = 38;
			this->button4->Text = L"Очистити фільтр";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &PencilForm::button4_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(20, 42);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(118, 17);
			this->label3->TabIndex = 35;
			this->label3->Text = L"Виробник олівця";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(20, 69);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(94, 17);
			this->label1->TabIndex = 33;
			this->label1->Text = L"Назва олівця";
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(142, 37);
			this->comboBox1->Margin = System::Windows::Forms::Padding(2);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(95, 28);
			this->comboBox1->TabIndex = 11;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &PencilForm::comboBox1_SelectedIndexChanged);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->Location = System::Drawing::Point(904, 320);
			this->button3->Margin = System::Windows::Forms::Padding(2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(158, 56);
			this->button3->TabIndex = 37;
			this->button3->Text = L"Видалити запис";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &PencilForm::button3_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(11, 320);
			this->button2->Margin = System::Windows::Forms::Padding(2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(153, 56);
			this->button2->TabIndex = 36;
			this->button2->Text = L"Редагувати запис";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &PencilForm::button2_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(492, 320);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(153, 56);
			this->button1->TabIndex = 35;
			this->button1->Text = L"Додати запис";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &PencilForm::button1_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->BackgroundColor = System::Drawing::SystemColors::Info;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(8) {
				this->Column1,
					this->Column2, this->Column3, this->Column4, this->Column5, this->Column6, this->Column7, this->Column8
			});
			this->dataGridView1->Location = System::Drawing::Point(9, 10);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(2);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(1053, 292);
			this->dataGridView1->TabIndex = 34;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"ID олівця";
			this->Column1->MinimumWidth = 6;
			this->Column1->Name = L"Column1";
			this->Column1->Width = 125;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Назва олівця";
			this->Column2->MinimumWidth = 6;
			this->Column2->Name = L"Column2";
			this->Column2->Width = 125;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Виробник олівця";
			this->Column3->MinimumWidth = 6;
			this->Column3->Name = L"Column3";
			this->Column3->Width = 125;
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"Товщина стержня";
			this->Column4->MinimumWidth = 6;
			this->Column4->Name = L"Column4";
			this->Column4->Width = 125;
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"Колір";
			this->Column5->MinimumWidth = 6;
			this->Column5->Name = L"Column5";
			this->Column5->Width = 125;
			// 
			// Column6
			// 
			this->Column6->HeaderText = L"Тип";
			this->Column6->MinimumWidth = 6;
			this->Column6->Name = L"Column6";
			this->Column6->Width = 125;
			// 
			// Column7
			// 
			this->Column7->HeaderText = L"Форма корпусу";
			this->Column7->MinimumWidth = 6;
			this->Column7->Name = L"Column7";
			this->Column7->Width = 125;
			// 
			// Column8
			// 
			this->Column8->HeaderText = L"Твердість";
			this->Column8->MinimumWidth = 6;
			this->Column8->Name = L"Column8";
			this->Column8->Width = 125;
			// 
			// PencilForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->ClientSize = System::Drawing::Size(1354, 388);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dataGridView1);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"PencilForm";
			this->Text = L"Олівці";
			this->Load += gcnew System::EventHandler(this, &PencilForm::PencilForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void PencilForm_Load(System::Object^ sender, System::EventArgs^ e) {
		try {
			connect->Open();
			SqlCeCommand^ command = gcnew SqlCeCommand("SELECT Name FROM Distributor", connect);
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			while (sqlRead->Read()) {
				comboBox1->Items->Add(sqlRead["Name"]);
			}
			connect->Close();
			sqlRead->Close();

			connect->Open();
			SqlCeCommand^ command2 = gcnew SqlCeCommand("SELECT Color FROM Lead", connect);
			SqlCeDataReader^ sqlRead2 = command2->ExecuteReader();
			while (sqlRead2->Read()) {
				comboBox2->Items->Add(sqlRead2["Color"]);
			}
			connect->Close();
			sqlRead2->Close();

			connect->Open();
			SqlCeCommand^ command3 = gcnew SqlCeCommand("SELECT type FROM Type", connect);
			SqlCeDataReader^ sqlRead3 = command3->ExecuteReader();
			while (sqlRead3->Read()) {
				comboBox3->Items->Add(sqlRead3["type"]);
			}
			connect->Close();
			sqlRead3->Close();
			if (comboBox1->Items->Count > 0)
			{
				comboBox1->SelectedIndex = -1;
				this->getPencil();
			}
		}
		catch (...) {
			MessageBox::Show("Щось виведено неправильно");
		}
	}
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		this->getPencil();
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		comboBox1->SelectedIndex = -1;
		textBox1->Clear();
		this->getPencil();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		EditPencil^ edit = gcnew EditPencil(0, getSelectedDistributorIndex(), -1, -1);
		edit->ShowDialog();
		this->getPencil();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		EditPencil^ edit = gcnew EditPencil(System::Convert::ToInt32(dataGridView1->Rows[dataGridView1->CurrentCell->RowIndex]->Cells[0]->Value));
		edit->ShowDialog();
		this->getPencil();
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			connect->Open();
			System::String^ query = "DELETE FROM Pencil WHERE [Id]=" +
				System::Convert::ToString(dataGridView1->Rows[dataGridView1->CurrentCell->RowIndex]->Cells[0]->Value);
			SqlCeCommand^ command = gcnew SqlCeCommand(query, connect);
			if (command->ExecuteNonQuery() > 0) {
				MessageBox::Show("Deleted!");
			}
			connect->Close();
			this->getPencil();
		}
		catch (...) {
			MessageBox::Show("Виберіть конкретний запис");
		}
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		System::String^ query = "SELECT * FROM [Pencil] WHERE Name ='" + textBox1->Text + "';";
		this->getQueryPencil(query);
	}
	private: System::Void comboBox2_SelectedValueChanged(System::Object^ sender, System::EventArgs^ e) {
		System::String^ query = "SELECT * FROM [Pencil] WHERE id_Lead IN (SELECT Id FROM [Lead] WHERE Color='" + comboBox2->Text + "');";
		this->getQueryPencil(query);
	}
private: System::Void comboBox3_SelectedValueChanged(System::Object^ sender, System::EventArgs^ e) {
	System::String^ query = "SELECT * FROM [Pencil] WHERE id_Type IN (SELECT Id FROM [Type] WHERE type='" + comboBox3->Text + "');";
	this->getQueryPencil(query);
}
};
}
