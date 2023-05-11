#pragma once
#include <stdexcept>
#include <String.h>
// підключення просторів імен std і System
using namespace std;
//using namespace System;
// оголошення класу
ref class Pencil {
	//закриті поля класу для збереження даних про олівці
	System::String^ name;
	int id_distributor;
	int id_lead;
	int id_type;
	int id;
public: // відкриті члени класу
	Pencil() {} // порожній конструктор
	// конструктор ініціалізації полів об’єктів класу
	Pencil(System::String^ n, int idd, int idl, int idt, int i) {
		this->name = n;
		this->id_distributor = idd;
		this->id_lead= idl;
		this->id_type = idt;
		if (i > 0) {
			this->id = i;
		}
		else throw invalid_argument("Невірне id");
		// обробка помилки при спробі ввести код запису, менший або рівний 0
	}
	void setName(System::String^ name) {
		if (name->Length != 0) {
			this->name = name;
		}
		else throw invalid_argument("Невірна назва");
		// обробка помилки при спробі залишити поле порожнім
	}
	System::String^ getName() {
		return this->name;
	}
	void setIDDistributor(int id_distributor) {
		if (id_distributor > 0) {
			this->id_distributor = id_distributor;
		}
		else throw invalid_argument("Невірний виробник");
		// обробка помилки при спробі залишити поле порожнім
	}
	int getIDDistributor() {
		return this->id_distributor;
	}
	void setIDLead(int id_lead) {
		if (id_lead > 0) {
			this->id_lead = id_lead;
		}
		else throw invalid_argument("Невірний стержень олівця");
		// обробка помилки при спробі залишити поле порожнім
	}
	int getIDLead() {
		return this->id_lead;
	}
	void setIDType(int id_type) {
		if (id_type > 0) {
			this->id_type = id_type;
		}
		else throw invalid_argument("Невірний тип");
		// обробка помилки при спробі залишити поле порожнім
	}
	int getIDType() {
		return this->id_type;
	}

	void setId(int id) {
		if (id > 0) {
			this->id = id;
		}
		else throw invalid_argument("Невірне id");
		// обробка помилки при спробі ввести код запису, менший або рівний 0
	}

	int getId() {
		return this->id;
	}
};
