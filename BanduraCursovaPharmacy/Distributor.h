#pragma once
#include <stdexcept>
#include <String.h>
// ���������� �������� ���� std � System
using namespace std;
//using namespace System;
// ���������� �����
ref class Distributor {
	//������ ���� ����� ��� ���������� ����� ��� ��������� ������
	System::String^ name;
	System::String^ country;
	System::String^ gmail;
	System::String^ adress;
	int id;
public: // ������ ����� �����
	Distributor() {} // ������� �����������
	// ����������� ����������� ���� �ᒺ��� �����
	Distributor(System::String^ n, System::String^ a, System::String^ g, System::String^ c, int i) {
		this->name = n;
		this->country = c;
		this->gmail = g;
		this->adress = a;
		if (i > 0) {
			this->id = i;
		}
		else throw invalid_argument("������ id");
		// ������� ������� ��� ����� ������ ��� ������, ������ ��� ����� 0
	}
	void setName(System::String^ name) {
		if (name->Length != 0) {
			this->name = name;
		}
		else throw invalid_argument("������ �����");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getName() {
		return this->name;
	}
	void setCountry(System::String^ country) {
		if (country->Length != 0) {
			this->country = country;
		}
		else throw invalid_argument("������ ����� �����");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getCountry() {
		return this->country;
	}
	void setGmail(System::String^ gmail) {
		if (gmail->Length != 0) {
			this->gmail = gmail;
		}
		else throw invalid_argument("������ ���������� ������");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getGmail() {
		return this->gmail;
	}
	void setAdress(System::String^ adress) {
		if (adress->Length != 0) {
			this->adress = adress;
		}
		else throw invalid_argument("������ ������");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getAdress() {
		return this->adress;
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
