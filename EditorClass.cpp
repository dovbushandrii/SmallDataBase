#include <iostream>
#include <string>
#include "DataBaseClasses.h"
#include <conio.h>

using namespace std;

void Editor::Edit(OnlineDataBase& base) {
	TrainShow show;
	TrainShow::ParamsforArrowMenu params = TrainShow::ParamsforArrowMenu();
	params.lines = {
		"Add train\n",
		"Change train\n",
		"Selective data delete\n",
		"Delete all data\n",
		"Back to menu\n"
	};
	while (!params.end) {
		show.ArrowsOnlyMenu(params);
		if ((int)params.returnkey == 13) {
			switch (params.line) {
			case 0: this->Adding(base); break;
			case 1: this->ChangeTrain(base); break;
			case 2: this->SelectionDeleting(base); break;
			case 3: this->DeleteAll(base); break;
			case 4: params.end = !params.end; break;
			}
		}
	}
	system("cls");
}

void Editor::Adding(OnlineDataBase& base) {
	TrainData newtrain;
	Adder addData;
	try {
		addData.addtrain(newtrain);
		newtrain.id = base.getdata().size() + 1;
		base.getdata().push_back(newtrain);
	}
	catch (exception & ex) {
		system("cls");
		cout << "Eding was canceled";
	}
}

void Editor::ChangeTrain(OnlineDataBase& base) {
	Adder addData;
	try {
		if (base.getdata().size() > 0) {
			int id;
			bool entered = false;
			system("cls");
			while (!entered) {
				cout << "Enter train ID: ";
				cin >> id;
				system("cls");
				if (id > base.getdata().size()) {
					cout << "Incorrect id,try again\n";
				}
				else {
					if (id <= 0) {
						throw exception("Unexpected ID");
					}
					entered = !entered;
				}
			}
			addData.addtrain(base.getdata()[id - 1]);
		}
	}
	catch (exception & ex) {
	}
}

void Editor::SelectionDeleting(OnlineDataBase& base) {
	if (base.getdata().size() > 0) {
		OnlineDataBase b;
		TrainShow show;
		bool end = false;
		int line = 0;
		while (!end) {
			system("cls");
			vector<TrainData> trains = base.getdata();
			cout << "Enter - Delete; Esc - Exit\n";
			for (int i = 0; i < trains.size(); i++) {
				if (i == line) {
					cout << "--> ";
					show.traindatatooutstring(trains[i]);
				}
				else {
					cout << "    ";
					show.traindatatooutstring(trains[i]);
				}
			}
			if (trains.size() != 0) {
				char key;
				key = _getch();
				if ((int)key == 27) end = !end;
				else if ((int)key != 13) {
					if ((int)key == -32) {
						key = _getch();
						if ((int)key == 72) {
							if (line > 0) line--;
							else line = trains.size() - 1;
						}
						else if ((int)key == 80) {
							if (line < trains.size() - 1) line++;
							else line = 0;
						}
					}
				}
				else {
					system("cls");
					cout << "Are you sure?(Enter - Yes;Esc - No)";
					char h = _getch();
					if (h == 13) {
						base.deleteelement(line);
						b.setid(base.getdata());
					}
				}
			}
			else end = !end;
		}
	}
}

void Editor::DeleteAll(OnlineDataBase& base) {
	system("cls");
	cout << "Are you sure?(Enter - Yes;Esc - No)";
	char h = _getch();
	if (h == 13) {
		base.deletedata();
	}
}