#pragma once
#include "EditType.h"
#include "Type.h"
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
	/// Summary for TypeForm
	/// </summary>
	public ref class TypeForm : public System::Windows::Forms::Form
	{
	private: List<Type^>^ TypeList;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;










		   SqlCeConnection^ connect;
	public:
		TypeForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			SqlCeEngine^ dbEngine = gcnew SqlCeEngine();
			dbEngine->LocalConnectionString = "Data Source=PencilDB.sdf";
			connect = gcnew SqlCeConnection(dbEngine->LocalConnectionString);
			TypeList = gcnew List<Type^>();
		}
		// метод відображення на формі даних про виробників
		void getType() {
			connect->Open();
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = "SELECT * FROM Type";
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			TypeList->Clear();
			while (sqlRead->Read()) {
				TypeList->Add(gcnew Type(
					System::Convert::ToString(sqlRead["type"]),
					System::Convert::ToString(sqlRead["form"]),
					System::Convert::ToString(sqlRead["hardness"]),
					System::Convert::ToInt32(sqlRead["Id"])
				));
			}
			connect->Close();
			this->updateTable();
		}

		//метод передачі запиту до БД на виконання
		void execute(System::String^ query) {
			connect->Open();
			SqlCeCommand^ command = gcnew SqlCeCommand(query, connect);
			command->ExecuteNonQuery();
			connect->Close();
		}

		// метод оновлення таблиці dataGridView
		void updateTable() {
			int i = 0;
			dataGridView1->Rows->Clear();
			for each (Type ^ Type in TypeList) {
				this->dataGridView1->Rows->Add();
				this->dataGridView1->Rows[i]->Cells[0]->Value = Type->getId();
				this->dataGridView1->Rows[i]->Cells[1]->Value = Type->getType();
				this->dataGridView1->Rows[i]->Cells[2]->Value = Type->getForm();
				this->dataGridView1->Rows[i]->Cells[3]->Value = Type->getHardness();
				++i;
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TypeForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button3;
	protected:
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
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->Location = System::Drawing::Point(369, 338);
			this->button3->Margin = System::Windows::Forms::Padding(2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(158, 56);
			this->button3->TabIndex = 11;
			this->button3->Text = L"Видалити запис";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &TypeForm::button3_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(9, 338);
			this->button2->Margin = System::Windows::Forms::Padding(2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(153, 56);
			this->button2->TabIndex = 10;
			this->button2->Text = L"Редагувати запис";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &TypeForm::button2_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(188, 338);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(153, 56);
			this->button1->TabIndex = 9;
			this->button1->Text = L"Додати запис";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &TypeForm::button1_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->BackgroundColor = System::Drawing::SystemColors::Info;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->Column1,
					this->Column2, this->Column3, this->Column4
			});
			this->dataGridView1->Location = System::Drawing::Point(9, 10);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(2);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(541, 324);
			this->dataGridView1->TabIndex = 8;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Номер форми";
			this->Column1->Name = L"Column1";
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Тип";
			this->Column2->Name = L"Column2";
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Форма корпусу";
			this->Column3->Name = L"Column3";
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"Твердість";
			this->Column4->Name = L"Column4";
			// 
			// TypeForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->ClientSize = System::Drawing::Size(559, 414);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dataGridView1);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"TypeForm";
			this->Text = L"Виробники олівців";
			this->Load += gcnew System::EventHandler(this, &TypeForm::TypeForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		//Запрограмовування відображення даних при запуску форми
	private: System::Void TypeForm_Load(System::Object^ sender, System::EventArgs^ e) {
		this->getType();
	}
		   // Запрограмовування кнопки Додати запис
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		EditType^ edit = gcnew EditType(-1);
		edit->ShowDialog();
		this->getType();
	}
		   // Запрограмовування кнопки Редагувати запис
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		EditType^ edit = gcnew EditType(System::Convert::ToInt32(dataGridView1->Rows[dataGridView1->CurrentCell->RowIndex]->Cells[0]->Value));
		edit->ShowDialog();
		this->getType();
	}
		   // Запрограмовування кнопки Видалити запис
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			connect->Open();
			System::String^ query = "DELETE FROM Type WHERE [Id]=" +
				System::Convert::ToString(dataGridView1->Rows[dataGridView1->CurrentCell->RowIndex]->Cells[0]->Value);
			SqlCeCommand^ command = gcnew SqlCeCommand(query, connect);
			if (command->ExecuteNonQuery() > 0) {
				MessageBox::Show("Видалено!");
			}
			connect->Close();
			this->getType();
		}
		catch (...) {
			MessageBox::Show("Виберіть конкретний запис");
		}
	}
	};
}
