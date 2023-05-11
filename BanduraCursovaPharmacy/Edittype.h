#pragma once

namespace BanduraCursovaPencil {

	//using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlServerCe;;

	/// <summary>
	/// Summary for EditType
	/// </summary>
	public ref class EditType : public System::Windows::Forms::Form
	{
		System::Data::SqlServerCe::SqlCeConnection^ connect;
	private: System::Windows::Forms::Label^ label4;

		   int TypeId;
	public:
		EditType(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		EditType(int dId) {
			InitializeComponent();
			SqlCeEngine^ dbEngine = gcnew SqlCeEngine();
			dbEngine->LocalConnectionString = "Data Source=PencilDB.sdf";
			connect = gcnew SqlCeConnection("Data Source=PencilDB.sdf");
			connect->Open();
			this->TypeId = dId;
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = "SELECT * FROM Type WHERE [Id]=@dId";
			command->Parameters->AddWithValue(
				"@dId",
				dId
			);
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			while (sqlRead->Read()) {
				textBox1->Text = System::Convert::ToString(sqlRead["Type"]);
				textBox2->Text = System::Convert::ToString(sqlRead["Form"]);
				textBox3->Text = System::Convert::ToString(sqlRead["Hardness"]);
			}
			connect->Close();
			sqlRead->Close();
		}
		int IfDuplicate()
		{
			int count;
			connect->Open();
			System::String^ query = "SELECT COUNT([type]) FROM[Type] WHERE [type] = '" + textBox1->Text + "' AND [form] = '" + textBox2->Text + "' AND [hardness] = '" + textBox3->Text + "' ;";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			bool hasRow = sqlRead->Read();
			if (hasRow)
			{
				count = System::Convert::ToInt32(sqlRead["Column1"]);
			}
			sqlRead->Close();
			connect->Close();
			return count;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EditType()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label3;
	protected:
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox1;

	private: System::Windows::Forms::Label^ label1;

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
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label3
			// 
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(2, 101);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(178, 28);
			this->label3->TabIndex = 24;
			this->label3->Text = L"Твердість";
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(192, 160);
			this->button2->Margin = System::Windows::Forms::Padding(2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(158, 51);
			this->button2->TabIndex = 23;
			this->button2->Text = L"Відміна";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &EditType::button2_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(6, 160);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(158, 51);
			this->button1->TabIndex = 22;
			this->button1->Text = L"Зберегти";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &EditType::button1_Click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(184, 101);
			this->textBox3->Margin = System::Windows::Forms::Padding(2);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(146, 28);
			this->textBox3->TabIndex = 21;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(184, 56);
			this->textBox2->Margin = System::Windows::Forms::Padding(2);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(146, 25);
			this->textBox2->TabIndex = 20;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(184, 11);
			this->textBox1->Margin = System::Windows::Forms::Padding(2);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(146, 28);
			this->textBox1->TabIndex = 19;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(5, 11);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(122, 24);
			this->label1->TabIndex = 17;
			this->label1->Text = L" Тип олівця";
			// 
			// label4
			// 
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(2, 52);
			this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(178, 49);
			this->label4->TabIndex = 25;
			this->label4->Text = L"Форма корпусу";
			// 
			// EditType
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(361, 225);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"EditType";
			this->Text = L"Додати виробника олівців";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		// Редагування запису
	private: void update() {
		try {
			connect->Open();
			System::String^ query = "UPDATE Type SET [type]='" + textBox1->Text + "', [form]='" + textBox2->Text + "', [hardness]='" + textBox3->Text + "' WHERE [Id]=" + this->TypeId + ";";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			if (command->ExecuteNonQuery() == 0) {
				MessageBox::Show("Змінено!");
			}
			connect->Close();
		}
		catch (...) {
			MessageBox::Show("Щось введено не правильно");
			this->Close();
		}
	}
		   // Добавлення запису
	private: void insert() {
		try {
			if (IfDuplicate() > 0)
			{
				MessageBox::Show("Такий виробник ліків вже існує");
				this->Close();
			}
			else
			{
				connect->Open();
				System::String^ query = "INSERT INTO Type([type], [form], [hardness])" +
					"VALUES('" + textBox1->Text + "','" + textBox2->Text + "','" + textBox3->Text + "');";
				SqlCeCommand^ command = connect->CreateCommand();
				command->CommandText = query;
				if (command->ExecuteNonQuery() > 0) {
					MessageBox::Show("Добавлено!");
				}
				connect->Close();
			}
		}
		catch (...) {
			MessageBox::Show("Щось введено не правильно");
			this->Close();
		}
	}

		   //Кнопка збереження даних
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBox1->Text->Length != 0 && textBox2->Text->Length != 0 && textBox3->Text->Length != 0) {
			if (this->TypeId == -1)
			{
				try {
					insert();
				}
				catch (...)
				{
					MessageBox::Show("Щось введено не правильно");
					this->Close();
				}
			}
			else
			{
				try {
					update();
				}
				catch (...)
				{
					MessageBox::Show("Щось введено не правильно");
					this->Close();
				}

			}
			this->Close();
		}
		else {
			MessageBox::Show("Добавте більше даних");
		}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}

	
};
}
