#pragma once
#include <stdexcept>
#include <String.h>
// ���������� �������� ���� std � System
using namespace std;
//using namespace System;
// ���������� �����
ref class Type {
	//������ ���� ����� ��� ���������� ����� ��� ��� ������
	System::String^ type;
	System::String^ form;
	System::String^ hardness;
	int id;
public: // ������ ����� �����
	Type() {} // ������� �����������
	// ����������� ����������� ���� �ᒺ��� �����
	Type(System::String^ t, System::String^ f, System::String^ h,  int i) {
		this->type = t;
		this->form = f;
		this->hardness = h;
		if (i > 0) {
			this->id = i;
		}
		else throw invalid_argument("������ id");
		// ������� ������� ��� ����� ������ ��� ������, ������ ��� ����� 0
	}
	void setType(System::String^ type) {
		if (type->Length != 0) {
			this->type = type;
		}
		else throw invalid_argument("������� ���");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getType() {
		return this->type;
	}
	void setForm(System::String^ form) {
		if (form->Length != 0) {
			this->form = form;
		}
		else throw invalid_argument("������ ����� �����");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getForm() {
		return this->form;
	}
	void setHardness(System::String^ hardness) {
		if (hardness->Length != 0) {
			this->hardness = hardness;
		}
		else throw invalid_argument("������ ��������");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getHardness() {
		return this->hardness;
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
};
