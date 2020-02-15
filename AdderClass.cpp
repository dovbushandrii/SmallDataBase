#include <iostream>
#include <conio.h>
#include <string>
#include "DataBaseClasses.h"
#include <cmath>

using namespace std;

void Adder::addtrain(TrainData& newtrain) {
	this->addnumber(newtrain);
	this->addname(newtrain);
	this->adddepdestination(newtrain);
	this->addtype(newtrain);
	this->adddate(newtrain);
	this->addrate(newtrain);
}

void Adder::addnumber(TrainData& newtrain) {
	bool entered = false;
	string variable;
	while (!entered) {
		system("cls");
		cout << "Enter train's number(4 numbers): " << variable;
		char key = _getch();
		if ((int)key == 8) {
			if (variable.size() != 0) {
				variable = variable.substr(0, (variable.size() - 1));
			}
		}
		else if ((int)key == 27) {
			throw exception("Esc");
		}
		else if ((int)key != 13) {
			if (variable.size() < 4) {
				if (key >= '0' && key <= '9') {
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
		cout << "Enter train's name(up to 15 symbols): ";
		cout << variable;
		char key = _getch();
		if ((int)key == 8) {
			if (variable.size() != 0) {
				variable = variable.substr(0, (variable.size() - 1));
			}
		}
		else if ((int)key == 27) {
			throw exception("Esc");
		}
		else if ((int)key != 13) {
			if (variable.size() < 15) {
				if (key != '\t') {
					variable += key;
				}
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
		cout << "Enter destination: " << firstpoint << f << variable;
		char key = _getch();
		if ((int)key == 8) {
			if (variable.size() != 0) {
				variable = variable.substr(0, (variable.size() - 1));
			}
		}
		else if ((int)key == 27) {
			throw exception("Esc");
		}
		else if ((int)key != 13) {
			if (variable.size() < 15) {
				if ((variable.size() == 0) && (key >= 'a' && key <= 'z') ) {
					variable += key + ('A' - 'a');
				}		//Заменяет первую букву города(места отправления или прибытия) на заглавную
				else {
					if (key != '\t') {
						variable += key;
					}
				}
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
	string standartline = "Chose train's type: ";
	bool end = false;
	Type newtype = Type::INTER;
	while (!end) {
		system("cls");
		cout << standartline;
		if (newtype == Type::INTER) { cout << "< International >"; }
		else if (newtype == Type::SPEED) { cout << "< Speed >"; }
		else if (newtype == Type::STANDART) { cout << "< Standart >"; }
		else if (newtype == Type::INTERCITY) { cout << "< Intercity >"; }
		char key;
		key = _getch();
		if (key == 13) {
			end = !end;
		}
		else if ((int)key == 27) {
			throw exception("Esc");
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

bool checkondate(string date) {
	if (date[0] < '4') {
		bool u1 = (date[0] == '3' && date[1] < '2');
		bool u2 = (date[0] < '3');
		if (u1 || u2) {
			if (date[2] < '2') {
				bool u3 = (date[2] == '1' && date[3] < '3');
				bool u4 = (date[2] < '1');
				if (u3 || u4) {
					return true;
				}
			}
		}
	}
	return false;
}
void enterdate(int& year, int& month, int& day, string phrase) {
	bool entered = false;
	string backorig = "ddmmyyyy";
	string newdate = "";
	while (!entered) {
		system("cls");
		string back = backorig;
		for (int i = 0; i < newdate.size(); i++) {
			back[i] = newdate[i];
		}
		cout << phrase << back.substr(0, 2) + '/' + back.substr(2, 2) + '/' + back.substr(4, back.size());
		char key = _getch();
		if ((int)key == 8) {
			if (newdate.size() != 0) {
				newdate = newdate.substr(0, newdate.size() - 1);
			}
		}
		else if ((int)key == 27) {
			throw exception("Esc");
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
				if (checkondate(newdate)) {
					entered = !entered;
				}
			}
		}
	}
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
}
bool checkontime(string date) {
	if (date[0] < '3') {
		bool u1 = (date[0] == '2' && date[1] < '4');
		bool u2 = (date[0] < '2');
		if (u1 || u2) {
			if (date[2] < '6') {
				return true;
			}
		}
	}
	return false;
}
void enterhours(int& hours, int& minutes, string phrase) {
	bool entered = false;
	string backorig = "hhmm";
	string newdate = "";
	while (!entered) {
		system("cls");
		string back = backorig;
		for (int i = 0; i < newdate.size(); i++) {
			back[i] = newdate[i];
		}
		cout << phrase << back.substr(0, 2) + ':' + back.substr(2, back.size() - 1);
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
				if (checkontime(newdate)) {
					entered = !entered;
				}
			}
		}
	}

	for (int i = 3; i > 1; i--) {
		minutes += (newdate[i] - '0') * pow(10, (3 - i));
	}
	for (int i = 1; i >= 0; i--) {
		hours += (newdate[i] - '0') * pow(10, (1 - i));
	}
}
void Adder::adddate(TrainData& newtrain) {
	int year = 0;
	int month = 0;
	int day = 0;
	int hours = 0;
	int minutes = 0;
	enterdate(year, month, day, "Enter date on arrival/departure: ");
	newtrain.date.day = day;
	newtrain.date.month = month;
	newtrain.date.year = year;
	enterhours(hours, minutes, "Enter arrival time: ");
	newtrain.date.hours = hours;
	newtrain.date.minutes = minutes;
	hours = 0;
	minutes = 0;
	enterhours(hours, minutes, "Enter departure time: ");
	newtrain.date.hours2 = hours;
	newtrain.date.minutes2 = minutes;
	system("cls");
}

void Adder::addrate(TrainData& newtrain) {
	bool entered = false;
	float rate;
	while (!entered) {
		system("cls");
		cout << "Enter rate(example 0.75): ";
		cin >> rate;
		if (rate >= 0) {
			entered = !entered;
		}
	}
	newtrain.rate = rate;
}