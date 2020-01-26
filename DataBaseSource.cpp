#include <iostream>
#include <conio.h>
#include <string>
#include "DataBaseClasses.h"

using namespace std;

void DataBaseInterface::Menu() {
	string lines[5] = {
		"Поиск поездов\n",
		"Настройки поиска\n",
		"Демострационный режим\n",
		"Проверка производительности\n",
		"Выход\n"
	};
	bool end = false;
	int line = 0;
	while (!end) {
		system("cls");
		cout << "Train DataBase 0.1\n\n";
		for (int i = 0; i < 5; i++) {
			if (i == line) {
				cout << "--> " << lines[i];
			}
			else {
				cout << "    " << lines[i];
			}
		}
		char key;
		key = _getch();
		if ((int)key != 13) {
			if ((int)key == -32) {
				key = _getch();
				if ((int)key == 72) {
					if (line > 0) line--;
					else line = 4;
				}
				else if ((int)key == 80) {
					if (line < 4) line++;
					else line = 0;
				}
			}
		}
		else {
			switch (line) {
				//case 0: this->Search(); break;
			case 1: this->Settings(); break;
				//case 2: this->Demo(); break;
				//case 3: this->Benchmark(); break;
			case 4: end = !end; break;
			}
		}
	}
	system("cls");

}

void DataBaseInterface::Settings(){
	string lines[7] = {
		"Отображать номер поезда при поиске:                  ",
		"Отображать название поезда при поиске:               ",
		"Отображать направление поезда при поиске:            ",
		"Отображать тип поезда при поиске:                    ",
		"Отображать время прибытия и отправления при поиске:  ",
		"Отображать рейтинг поезда при поиске:                ",
		"Выход из настроек\n"
	};
	bool end = false;
	int line = 0;
	while (!end) {
		system("cls");
		for (int i = 0; i < 7; i++) {
			if (i == line) {
				cout << "--> " << lines[i];
			}
			else {
				cout << "    " << lines[i];
			}
			if (i != 6) {
				if (settings[i] == ShowOptions::SHOWN) cout << "< Äà >\n";
				else cout << "< Íåò >\n";
			}
		}
		char key;
		key = _getch();
		if (key == 13 && line == 6) {
			end = !end;
		}
		else {
			if (key == -32) {
				key = _getch();
				if ((int)key == 77 || (int)key == 75) {
					if (settings[line] == ShowOptions::SHOWN) settings[line] = ShowOptions::NOTSHOWN;
					else settings[line] = ShowOptions::SHOWN;
				}
				else if ((int)key == 72) {
					if (line > 0) line--;
					else line = 6;
					}
				else if ((int)key == 80) {
					if (line < 6) line++;
					else line = 0;
				}
			}
		}
	}
}
