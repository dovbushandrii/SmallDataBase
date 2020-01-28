#include <iostream>
#include <conio.h>
#include <string>
#include "DataBaseClasses.h"
#include <cmath>

using namespace std;

void DataBaseInterface::Menu() {
	string lines[6] = {
		"Поиск поездов\n",
		"Изменение данных\n",
		"Настройки поиска\n",
		"Демострационный режим\n",
		"Проверка производительности\n",
		"Выход\n"
	};
	bool end = false;
	int line = 0;
	while (!end) {
		system("cls");
		cout << "Train DataBase 0.2\n\n";

		for (int i = 0; i < 6; i++) {
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
					else line = 5;
				}
				else if ((int)key == 80) {
					if (line < 5) line++;
					else line = 0;
				}
			}
		}
		else {
			switch (line) {
			case 0: this->Search(); break;
			case 1: this->Edit();break;
			case 2: this->Settings(); break;
				//case 2: this->Demo(); break;
				//case 3: this->Benchmark(); break;
			case 5: end = !end; break;
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
				if (settings[i] == ShowOptions::SHOWN) cout << "< Да >\n";
				else cout << "< Нет >\n";
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
void DataBaseInterface::Edit() {
	string lines[3] = {
		"Добавление поездов\n",
		"Удаление данных\n",
		"Выход\n"
	};
	bool end = false;
	int line = 0;
	while (!end) {
		system("cls");
		for (int i = 0; i < 3; i++) {
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
					else line = 2;
				}
				else if ((int)key == 80) {
					if (line < 2) line++;
					else line = 0;
				}
			}
		}
		else {
			switch (line) {
			case 0: this->Adding(); break;
				//case 1: this->Deleting(); break;
			case 2: end = !end; break;
			}
		}
	}
	system("cls");
}
void DataBaseInterface::Adding() {
	TrainData newtrain;
	Adder addData;
	addData.addnumber(newtrain);
	addData.addname(newtrain);
	addData.adddepdestination(newtrain);
	addData.addtype(newtrain);
	addData.adddate(newtrain);
	addData.addrate(newtrain);
	base.getdata().push_back(newtrain);
}
void DataBaseInterface::Search() {
	system("cls");
	vector<TrainData> a = base.getdata();
	for (int i = 0; i < a.size(); i++) {
		traindatatooutstring(a[i]);
	}
	system("pause");
}
void DataBaseInterface::traindatatooutstring(TrainData train) {
	string res;
	if (settings[0] == ShowOptions::SHOWN) { cout << train.no << "  "; };
	if (settings[1] == ShowOptions::SHOWN) { cout << train.name << "  "; };
	if (settings[2] == ShowOptions::SHOWN) { cout << train.departurepoint << "->" << train.destination << "  "; };
	if (settings[3] == ShowOptions::SHOWN) {
		cout << "Тип: ";
		if (train.type == Type::INTER) { cout << "Международный"; }
		else if (train.type == Type::SPEED) { cout << "Скоростной"; }
		else if (train.type == Type::STANDART) { cout << "Стандарт"; }
		else { cout << "Междугородний"; }
		cout << "  ";
	};
	if (settings[5] == ShowOptions::SHOWN) { cout << "  Рейтинг: " << train.rate << "   "; };
	if (settings[4] == ShowOptions::SHOWN) { 
		cout << train.date.hours << ":" << train.date.minutes << "  " << train.date.day << '/' << train.date.month << '/' << train.date.year;
	};
	cout << endl;

	
}

void Adder::addnumber(TrainData& newtrain) {
	bool entered = false;
	string variable;
	while (!entered) {
		system("cls");
		cout << "Введите номер поезда(4 знака): " << variable;
		char key = _getch();
		if ((int)key == 8) {
			if (variable.size() != 0) {
				variable = variable.substr(0, (variable.size() - 1));
			}
		}
		else if ((int)key != 13) {
			if (variable.size() < 4) {
				int num = key - '0';
				if (num > -1 && num < 10) {
					variable += key;
				}
			}
		}
		else {
			if (variable.size() > 3) {
				entered = !entered;
			}
		}
	}
	newtrain.no = variable;
}
void Adder::addname(TrainData& newtrain) {
	bool entered = false;
	string variable;
	while (!entered) {
		system("cls");
		cout << "Введите имя поезда(до 15 символов): " << variable;
		char key = _getch();
		if ((int)key == 8) {
			if (variable.size() != 0) {
				variable = variable.substr(0, (variable.size() - 1));
			}
		}
		else if ((int)key != 13) {
			if (variable.size() < 15) {
				variable += key;
			}
		}
		else {
			entered = !entered;
		}
	}
	newtrain.name = variable;
}
void Adder::adddepdestination(TrainData& newtrain) {
	bool entered = false;
	string variable;
	string firstpoint;
	bool deppoint = false; // проверка на введение пункта отправления
	while (!entered) {
		system("cls");
		string f;
		if (deppoint) {
			f = "->";
		}
		cout << "Введите направление поезда: " << firstpoint << f << variable;
		char key = _getch();
		if ((int)key == 8) {
			if (variable.size() != 0) {
				variable = variable.substr(0, (variable.size() - 1));
			}
		}
		else if ((int)key != 13) {
			if (variable.size() < 15) {
				if ((variable.size() == 0) && (key >= 'a' && key <= 'z')) {
					variable += key + ('A' - 'a');
				}		//Заменяет первую букву города(места отправления или прибытия) на заглавную
				else variable += key;
			}
		}
		else {
			if (variable.size() > 0) {
				if (!deppoint) {
					deppoint = !deppoint;
					firstpoint = variable;
					variable = "";
				}
				else entered = !entered;
			}
		}
	}
	newtrain.departurepoint = firstpoint;
	newtrain.destination = variable;
}
void Adder::addtype(TrainData& newtrain) {
	string standartline = "Выберите тип поезда: ";
	bool end = false;
	Type newtype = Type::INTER;
	while (!end) {
		system("cls");
		cout << standartline;
		if (newtype == Type::INTER) { cout << "< Международный >"; }
		else if (newtype == Type::SPEED) { cout << "< Скоростной >"; }
		else if (newtype == Type::STANDART) { cout << "< Стандарт >"; }
		else { cout << "< Междугородний >"; }
		char key;
		key = _getch();
		if (key == 13) {
			end = !end;
		}
		else {
			if (key == -32) {
				key = _getch();
				if ((int)key == 77) {
					switch (newtype) {
					case INTER: newtype = Type::SPEED; break;
					case SPEED: newtype = Type::STANDART; break;
					case STANDART: newtype = Type::INTERCITY; break;
					case INTERCITY: newtype = Type::INTER; break;
					}
				}
				else if ((int)key == 75) {
					switch (newtype) {
					case INTER: newtype = Type::INTERCITY; break;
					case SPEED: newtype = Type::INTER; break;
					case STANDART: newtype = Type::SPEED; break;
					case INTERCITY: newtype = Type::STANDART; break;
					}
				}
			}
		}

	}
	newtrain.type = newtype;
}
void Adder::adddate(TrainData& newtrain) {
	bool entered = false;
	string backorig = "ddmmyyyy";
	string newdate = "";
	while (!entered) {
		system("cls");
		string back = backorig;
		for (int i = 0; i < newdate.size(); i++) {
			back[i] = newdate[i];
		}
		cout << "Введите дату отправления поезда: " << back.substr(0,2) + '/' + back.substr(2, 2) + '/' + back.substr(4,back.size());
		char key = _getch();
		if ((int)key == 8) {
			if (newdate.size() != 0) {
				newdate = newdate.substr(0, newdate.size() - 1);
			}
		}
		else if ((int)key != 13) {
			int num = key - '0';
			if (num > -1 && num < 10) {
				if (newdate.size() < 8) {
					newdate += key;
				}
			}
		}
		else {
			if (newdate.size() == 8) {
				entered = !entered;
			}
		}
	}
	int year = 0;
	int month = 0;
	int day = 0;
	int hours = 0;
	int minutes = 0;
	system("cls");
	for (int i = 7; i > 3; i--) {
		year += (newdate[i] - '0') * pow(10, (7 - i));
	}
	for (int i = 3; i > 1; i--) {
		month += (newdate[i] - '0') * pow(10, (3 - i));
	}
	for (int i = 1; i >= 0; i--) {
		day += (newdate[i] - '0') * pow(10, (1 - i));
	}
	entered = !entered;
	backorig = "hhmm";
	newdate = "";
	while (!entered) {
		system("cls");
		string back = backorig;
		for (int i = 0; i < newdate.size(); i++) {
			back[i] = newdate[i];
		}
		cout << "Введите время отправления поезда: " << back.substr(0, 2) + ':' + back.substr(2, back.size()-1);
		char key = _getch();
		if ((int)key == 8) {
			if (newdate.size() != 0) {
				newdate = newdate.substr(0, newdate.size() - 1);
			}
		}
		else if ((int)key != 13) {
			int num = key - '0';
			if (num > -1 && num < 10) {
				if (newdate.size() < 4) {
					newdate += key;
				}
			}
		}
		else {
			if (newdate.size() == 4) {
				entered = !entered;
			}
		}
	}
	for (int i = 3; i > 1; i--) {
		minutes += (newdate[i] - '0') * pow(10, (3 - i));
	}
	for (int i = 1; i >= 0; i--) {
		hours += (newdate[i] - '0') * pow(10, (1 - i));
	}
	newtrain.date.day = day;
	newtrain.date.month = month;
	newtrain.date.year = year;
	newtrain.date.hours = hours;
	newtrain.date.minutes = minutes;
}
void Adder::addrate(TrainData& newtrain) {
	bool entered = false;
	float rate;
	while (!entered) {
		system("cls");
		cout << "Введите рейтинг(пример 0.75): ";
		cin >> rate;
		if (rate <= 1 && rate >= 0) {
			entered = !entered;
		}
	}
	newtrain.rate = rate;
}



void Searcher::sortby(vector<TrainData>& SearchResult, SortBy filter) {

}

