#pragma once
#pragma once
#include <stdexcept>
#include <String.h>
// ���������� �������� ���� std � System
using namespace std;
//using namespace System;
// ���������� �����
ref class Lead {
	//������ ���� ����� ��� ���������� ����� ��� ������� �����
	float thickness;
	System::String^ color;
	int id;
public: // ������ ����� �����
	Lead() {} // ������� �����������
	// ����������� ����������� ���� �ᒺ��� �����
	Lead(float t, System::String^ c, int i) {
		this->thickness = t;
		this->color = c;
		if (i > 0) {
			this->id = i;
		}
		else throw invalid_argument("������ id");
		// ������� ������� ��� ����� ������ ��� ������, ������ ��� ����� 0
	}
	void setColor(System::String^ color) {
		if (color->Length != 0) {
			this->color = color;
		}
		else throw invalid_argument("������� ����");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getColor() {
		return this->color;
	}
	void setId(int id) {
		if (id > 0) {
			this->id = id;
		}
		else throw invalid_argument("������ id");
		// ������� ������� ��� ����� ������ ��� ������, ������ ��� ����� 0
	}

	int getId() {
		return this->id;
	}
	void setThickness(float thickness) {
		if (thickness > 0) {
			this->thickness = thickness;
		}
		else throw invalid_argument("������ �������");
		// ������� ������� ��� ����� ������ ��� ������, ������ ��� ����� 0
	}

	float getThickness() {
		return this->thickness;
	}
};
