#pragma once
#pragma once
#include <stdexcept>
#include <String.h>
// підключення просторів імен std і System
using namespace std;
//using namespace System;
// оголошення класу
ref class Lead {
	//закриті поля класу для збереження даних про товщину олівця
	float thickness;
	System::String^ color;
	int id;
public: // відкриті члени класу
	Lead() {} // порожній конструктор
	// конструктор ініціалізації полів об’єктів класу
	Lead(float t, System::String^ c, int i) {
		this->thickness = t;
		this->color = c;
		if (i > 0) {
			this->id = i;
		}
		else throw invalid_argument("Невірне id");
		// обробка помилки при спробі ввести код запису, менший або рівний 0
	}
	void setColor(System::String^ color) {
		if (color->Length != 0) {
			this->color = color;
		}
		else throw invalid_argument("Невірний колір");
		// обробка помилки при спробі залишити поле порожнім
	}
	System::String^ getColor() {
		return this->color;
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
	void setThickness(float thickness) {
		if (thickness > 0) {
			this->thickness = thickness;
		}
		else throw invalid_argument("Невірна товщина");
		// обробка помилки при спробі ввести код запису, менший або рівний 0
	}

	float getThickness() {
		return this->thickness;
	}
};
