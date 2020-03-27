#include <iostream>
#include <conio.h>
#include <string>
#include "TrainShowClass.h"
#include <thread>
#include <chrono>

using namespace std;

void TrainShow::traindatatooutstring(TrainData train, ShowOptions settings[] ){
	string res;
	cout << "ID: " << train.id << "  ";
	if (settings[0] == ShowOptions::SHOWN) { cout << train.no << "  "; };
	if (settings[1] == ShowOptions::SHOWN) { cout << train.name << "  "; };
	if (settings[2] == ShowOptions::SHOWN) { cout << train.departurepoint << "->" << train.destination << "  "; };
	if (settings[3] == ShowOptions::SHOWN) {
		cout << "Type: ";
		if (train.type == Type::INTER) { cout << "International"; }
		else if (train.type == Type::SPEED) { cout << "Speed"; }
		else if (train.type == Type::STANDART) { cout << "Standart"; }
		else if (train.type == Type::INTERCITY) { cout << "Intercity"; }
		cout << "  ";
	};
	if (settings[5] == ShowOptions::SHOWN) { cout << "  Rate: " << train.rate << "   "; };
	if (settings[4] == ShowOptions::SHOWN) {
		cout << " Arrival: ";
		if (train.date.hours < 10) { cout << '0'; }
		cout << train.date.hours << ":";
		if (train.date.minutes < 10) { cout << '0'; }
		cout << train.date.minutes;
		cout << "  Departure: ";
		if (train.date.hours2 < 10) { cout << '0'; }
		cout << train.date.hours2 << ":";
		if (train.date.minutes2 < 10) { cout << '0'; }
		cout << train.date.minutes2 << "  ";
		if (train.date.day < 10) { cout << '0'; }
		cout << train.date.day << '/';
		if (train.date.month < 10) { cout << '0'; }
		cout << train.date.month << '/';
		cout << train.date.year;
	};
	cout << endl;
}

void TrainShow::traindatatooutstring(TrainData train) {
	ShowOptions settings[6];
	for (int i = 0; i < 6; i++) {
		settings[i] = ShowOptions::SHOWN;
	}
	this->traindatatooutstring(train, settings);
}

void TrainShow::showtrain(TrainData train) {
	cout << "Number:        " << train.no << endl;
	cout << "Name:          " << train.name << endl;
	cout << "Direction:     " << train.departurepoint << "->" << train.destination << endl;
	cout << "Type:          ";
	if (train.type == Type::INTER) { cout << "International"; }
	else if (train.type == Type::SPEED) { cout << "Speed"; }
	else if (train.type == Type::STANDART) { cout << "Standart"; }
	else if (train.type == Type::INTERCITY) { cout << "Intercity"; }
	cout << endl;
	cout << "Rate:          " << train.rate << endl;
	cout << "Arrival:       ";
	if (train.date.hours < 10) { cout << '0'; }
	cout << train.date.hours << ":";
	if (train.date.minutes < 10) { cout << '0'; }
	cout << train.date.minutes << endl;
	cout << "Departure:     ";
	if (train.date.hours2 < 10) { cout << '0'; }
	cout << train.date.hours2 << ":";
	if (train.date.minutes2 < 10) { cout << '0'; }
	cout << train.date.minutes2 << endl;
	cout << "Date:          ";
	if (train.date.day < 10) { cout << '0'; }
	cout << train.date.day << '/';
	if (train.date.month < 10) { cout << '0'; }
	cout << train.date.month << '/';
	cout << train.date.year << endl;

}

void showlist(vector<TrainData> trains,int line, ShowOptions settings[]){
	TrainShow t;
	int size = 20;
	if ((int)trains.size() < 20) {
		size = (int)trains.size();
	}
	for (int i = 0; i < size + 1; i++) {
		if (i == 0) {
		}
		else {
			if (i == line) {
				cout << "--> ";
				t.traindatatooutstring(trains[i - 1], settings);
			}
			else {
				cout << "    ";
				t.traindatatooutstring(trains[i - 1], settings);
			}
		}
	}
	if ((int)trains.size() > 20) {
		cout << "    ..." << endl;
	}
}

void TrainShow::ArrowSearchMenu(TrainShow::ParamsforSearchMenu& params, ShowOptions settings[]) {
	system("cls");
	cout << params.mainline << endl;
	thread th(showlist, params.trains, params.line, settings);
	th.detach();
	char key;
	params.returnkey = '\0';
	params.returnfunckey = 0;
	key = _getch();
	if ((int)key == 27) params.end = !params.end;
	else if ((int)key != 13) {
		if ((int)key == -32) {
			key = _getch();
			if ((int)key == 72) {
				if (params.line > 0) params.line--;
				else params.line =(int) params.trains.size();
			}
			else if ((int)key == 80) {
				if (params.line < (int)params.trains.size()) params.line++;
				else params.line = 0;
			}
			else {
				params.returnfunckey = (int)key;
			}
		}
		else if ((int)key != 0) {
			if ((int)key == 8) {
				if (params.searchstr.size() > 0) {
					params.searchstr = params.searchstr.substr(0, (int)params.searchstr.size() - 1);
				}
			}
			else {
				params.returnkey = key;
			}
		}
	}
	else {
		if (params.line != 0) {
			system("cls");
			this->showtrain(params.trains[params.line - 1]);
			system("pause");
		}
	}
}

void TrainShow::ArrowsOnlyMenu(TrainShow::ParamsforArrowMenu& params) {
	system("cls");
	params.returnkey = '\0';

	for (int i = 0; i < (int)params.lines.size(); i++) {
		if (i == params.line) {
			cout << "--> " << params.lines[i];
		}
		else {
			cout << "    " << params.lines[i];
		}
	}

	char key;
	key = _getch();
	if ((int)key == 27) { params.returnkey = key; params.end = !params.end; }
	else if ((int)key != 13) {
		if ((int)key == -32) {
			key = _getch();
			/* нопка вверх*/
			if ((int)key == 72) {
				if (params.line > 0) params.line--;
				else params.line = (int)params.lines.size()-1;
			}
			/* нопка вниз*/
			else if ((int)key == 80) {
				if (params.line < (int)params.lines.size()-1) params.line++;
				else params.line = 0;
			}
			/* нопки влево и вправо*/
			else if ((int)key == 77 || (int)key == 75) {
				params.returnkey = key;
			}
		}
	}
	else {
		params.returnkey = key;
	}
}