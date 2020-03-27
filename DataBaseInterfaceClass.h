#pragma once
#include "OnlineDataBase.h"

enum ShowOptions {
	SHOWN,
	NOTSHOWN
};

class DataBaseInterface {
public:
	DataBaseInterface() {
		for (int i = 0; i < 6; i++) {
			settings[i] = ShowOptions::SHOWN;
		}
	} // done
	void Menu(); // done
private:
	ShowOptions settings[6];   // ��������� ����������� ������  � ������ (�����, ��������, �����������, ���, ����, �������)
	OnlineDataBase base;	   //Online ���� ������
	void Settings(); // done
	void Search();
	void searchbyname();
	void searchbyrate();
	void searchbydate();
};