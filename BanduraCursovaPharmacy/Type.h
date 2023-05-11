#pragma once
#include <stdexcept>
#include <String.h>
// підключення просторів імен std і System
using namespace std;
//using namespace System;
// оголошення класу
ref class Type {
	//закриті поля класу для збереження даних про тип олівців
	System::String^ type;
	System::String^ form;
	System::String^ hardness;
	int id;
public: // відкриті члени класу
	Type() {} // порожній конструктор
	// конструктор ініціалізації полів об’єктів класу
	Type(System::String^ t, System::String^ f, System::String^ h,  int i) {
		this->type = t;
		this->form = f;
		this->hardness = h;
		if (i > 0) {
			this->id = i;
		}
		else throw invalid_argument("Невірне id");
		// обробка помилки при спробі ввести код запису, менший або рівний 0
	}
	void setType(System::String^ type) {
		if (type->Length != 0) {
			this->type = type;
		}
		else throw invalid_argument("Невірний тип");
		// обробка помилки при спробі залишити поле порожнім
	}
	System::String^ getType() {
		return this->type;
	}
	void setForm(System::String^ form) {
		if (form->Length != 0) {
			this->form = form;
		}
		else throw invalid_argument("Невірна форма олівця");
		// обробка помилки при спробі залишити поле порожнім
	}
	System::String^ getForm() {
		return this->form;
	}
	void setHardness(System::String^ hardness) {
		if (hardness->Length != 0) {
			this->hardness = hardness;
		}
		else throw invalid_argument("Невірна твердість");
		// обробка помилки при спробі залишити поле порожнім
	}
	System::String^ getHardness() {
		return this->hardness;
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
