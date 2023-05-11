#pragma once
#include <stdexcept>
#include <String.h>
// ���������� �������� ���� std � System
using namespace std;
//using namespace System;
// ���������� �����
ref class Pencil {
	//������ ���� ����� ��� ���������� ����� ��� �����
	System::String^ name;
	int id_distributor;
	int id_lead;
	int id_type;
	int id;
public: // ������ ����� �����
	Pencil() {} // ������� �����������
	// ����������� ����������� ���� �ᒺ��� �����
	Pencil(System::String^ n, int idd, int idl, int idt, int i) {
		this->name = n;
		this->id_distributor = idd;
		this->id_lead= idl;
		this->id_type = idt;
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
	void setIDDistributor(int id_distributor) {
		if (id_distributor > 0) {
			this->id_distributor = id_distributor;
		}
		else throw invalid_argument("������� ��������");
		// ������� ������� ��� ����� �������� ���� �������
	}
	int getIDDistributor() {
		return this->id_distributor;
	}
	void setIDLead(int id_lead) {
		if (id_lead > 0) {
			this->id_lead = id_lead;
		}
		else throw invalid_argument("������� �������� �����");
		// ������� ������� ��� ����� �������� ���� �������
	}
	int getIDLead() {
		return this->id_lead;
	}
	void setIDType(int id_type) {
		if (id_type > 0) {
			this->id_type = id_type;
		}
		else throw invalid_argument("������� ���");
		// ������� ������� ��� ����� �������� ���� �������
	}
	int getIDType() {
		return this->id_type;
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
