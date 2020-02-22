#include <iostream>
#include <string>
#include "DataBaseClasses.h"
#include "UsefulFunc.h"
#include <thread>

using namespace std;

void DataBaseInterface::Menu() {
	FileManager fim;
	TrainShow show;
	thread th([](OnlineDataBase& base) {
		FileManager fim;
		fim.DownloadData(base);
		},std::ref(base));

	TrainShow::ParamsforArrowMenu params = TrainShow::ParamsforArrowMenu();
	params.lines = {
		"Train Search\n",
		"Editing\n",
		"Search Settings\n",
		"Demo\n",
		"Benchmark\n",
		"Exit\n",
	};	
	while (!params.end) {
		show.ArrowsOnlyMenu(params);
		if ((int)params.returnkey == 13) {
			switch (params.line) {
			case 0: this->Search(); break;
			case 1: {
				Editor edit;
				edit.Edit(base);
				break;
			}
			case 2: this->Settings(); break;
			case 3: {
				Demonstrator dem;
				dem.Demo();
				break;
			}
			case 4: {
				Benchmark ben;
				ben.BenchmarkTest(".txt");
				ben.BenchmarkTest(".bin");
				break;
			}
			case 5: {
				fim.StoringData(base);
				params.end = !params.end;
				break;
			}
			}

		}
		else if ((int)params.returnkey == 27) {
			fim.StoringData(base);
		}
	}
	th.join();

	system("cls");
}

void DataBaseInterface::Settings() {
	vector<string> lines = {
		"Show train's number:                                 ",
		"Show train's name:                                   ",
		"Show train's direction:                              ",
		"Show train's type:                                   ",
		"Show train's date&time of arrival/departure:         ",
		"Show train's rate:                                   ",
		"Back to menu\n"
	};
	TrainShow show;
	TrainShow::ParamsforArrowMenu params = TrainShow::ParamsforArrowMenu();
	params.lines = lines;
	while (!params.end) {
		for (int i = 0; i < lines.size()-1; i++) {
			if (settings[i] == ShowOptions::SHOWN) {
				params.lines[i] = lines[i] +  "< Yes >\n";
			}
			else params.lines[i] = lines[i] + "< No >\n";
		}

		show.ArrowsOnlyMenu(params);
	
		if ((int)params.returnkey == 77 || (int)params.returnkey == 75) {
			if (settings[params.line] == ShowOptions::SHOWN) settings[params.line] = ShowOptions::NOTSHOWN;
			else settings[params.line] = ShowOptions::SHOWN;
		}
		if ((int)params.returnkey == 13) {
			if (params.line == params.lines.size() - 1) {
				params.end = !params.end;
			}
		}
	}
	system("cls");
}

void DataBaseInterface::Search() {
	TrainShow show;
	TrainShow::ParamsforArrowMenu params = TrainShow::ParamsforArrowMenu();
	params.lines = {
		"Search by name\n",
		"Search by rate\n",
		"Search by date\n",
		"Back to menu\n"
	};
	while (!params.end) {
		show.ArrowsOnlyMenu(params);
		if ((int)params.returnkey == 13) {
			switch (params.line) {
			case 0: this->searchbyname(); break;
			case 1: this->searchbyrate(); break;
			case 2: this->searchbydate(); break;
			case 3: params.end = !params.end; break;
			}
		}
	}
	system("cls");
}

void DataBaseInterface::searchbyname() {
	TrainShow show;
	Searcher seeker;
	TrainShow::ParamsforSearchMenu params = TrainShow::ParamsforSearchMenu();
	system("cls");
	cout << "Loading train's data...";
	vector<TrainData> train = base.getdata();
	while (!params.end) {
		params.mainline = "Enter name: " + params.searchstr;
		params.trains = seeker.searchtrains(train, params.searchstr);

		show.ArrowSearchMenu(params, settings);

		if (params.returnkey != '\0') {
			if (params.searchstr.size() < 15) {
				params.searchstr += params.returnkey;
			}
		}
		
	}
}
void DataBaseInterface::searchbyrate() {
	TrainShow show;
	Searcher seeker;
	system("cls");
	cout << "Loading train's data...";
	vector<TrainData> train = base.getdata();
	TrainShow::ParamsforSearchMenu params = TrainShow::ParamsforSearchMenu();
	while (!params.end) {
		params.mainline = "Enter rate: " + params.searchstr;
		float rate = strtofloat(params.searchstr);
		params.trains = seeker.searchtrains(train, rate);

		show.ArrowSearchMenu(params, settings);

		if (params.returnkey != '\0') {
			if ((params.returnkey >= '0' && params.returnkey <= '9') || params.returnkey == '.') {
				if (params.searchstr.size() <= 255) {
					params.searchstr += params.returnkey;
				}
			}
		}
	}
}
void DataBaseInterface::searchbydate()
{
	TrainShow show;
	Searcher seeker;
	string background = "hhmmddmmyyyy";
	system("cls");
	cout << "Loading train's data...";
	vector<TrainData> train = base.getdata();
	TrainShow::ParamsforSearchMenu params = TrainShow::ParamsforSearchMenu();
	while (!params.end) {
		string back = background;
		for (int i = 0; i < params.searchstr.size(); i++) {
			back[i] = params.searchstr[i];
		}
		params.mainline = "Enter date&time of departure: " + back.substr(0, 2) + ':' + back.substr(2, 2) + "	";
		params.mainline += back.substr(4, 2) + '/' + back.substr(6, 2) + '/' + back.substr(8, 4);
		Date date = stringtodate(params.searchstr);
		params.trains = seeker.searchtrains(train, date);
		show.ArrowSearchMenu(params, settings);

		if (params.returnkey != '\0') {
			if (params.searchstr.size() < 12) {
				params.searchstr += params.returnkey;
			}
		}
	}
}


