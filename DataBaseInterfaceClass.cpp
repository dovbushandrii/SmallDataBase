#include <iostream>
#include <string>
#include "DataBaseInterfaceClass.h"
#include "FileManagerClass.h"
#include "TrainShowClass.h"
#include "EditorClass.h"
#include "DemonstratorClass.h"
#include "BenchmarkClass.h"
#include "SearcherClass.h"
#include "SorterClass.h"
#include "UsefulFunc.h"
#include <thread>

using namespace std;

void DataBaseInterface::Menu() {
	FileManager fim;
	TrainShow show;
	thread th([](OnlineDataBase& base) {
		FileManager fim;
		fim.DownloadData(base);
		},ref(base));

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
		for (int i = 0; i < (int)lines.size()-1; i++) {
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

string setnewtyperight(Sorter::SortType& typeofsort) {
	string a[10] = {
		"<NONE>",
		"<NUMBER>",
		"<NAME>",
		"<DEPARTURE POINT>",
		"<DESTINATION POINT>",
		"<ARRIVAL TIME>",
		"<DEPARTURE TIME>",
		"<TYPE>",
		"<DATE>",
		"<RATE>",
	};
	int numb = (int)typeofsort;
	numb++;
	if (numb > 9) numb = 0;
	typeofsort = (Sorter::SortType)numb;
	
	return a[numb];
}

string setnewtypeleft(Sorter::SortType& typeofsort) {
	string a[10] = {
		"<NONE>",
		"<NUMBER>",
		"<NAME>",
		"<DEPARTURE POINT>",
		"<DESTINATION POINT>",
		"<ARRIVAL TIME>",
		"<DEPARTURE TIME>",
		"<TYPE>",
		"<DATE>",
		"<RATE>",
	};
	int numb = (int)typeofsort;
	numb--;
	if (numb < 0) numb = 9;
	typeofsort = (Sorter::SortType)numb;
	return a[numb];
}

void DataBaseInterface::searchbyname() {
	TrainShow show;
	Searcher seeker;
	Sorter s;
	TrainShow::ParamsforSearchMenu params = TrainShow::ParamsforSearchMenu();
	system("cls");
	cout << "Loading train's data...";
	vector<TrainData> train = base.getdata();
	string sortset = "<None>";
	Sorter::SortType typeofsort = Sorter::SortType::NONE;
	while (!params.end) {
		params.mainline = " Type of sort: " + sortset + "\n Enter name: " + params.searchstr ;
		params.trains = seeker.searchtrains(train, params.searchstr);
		s.sort(params.trains, typeofsort);

		show.ArrowSearchMenu(params, settings);

		if (params.returnkey != '\0') {
			if (params.searchstr.size() < 15) {
				params.searchstr += params.returnkey;
			}
		}
		if (params.returnfunckey != 0) {
			if (params.returnfunckey == 75) {
				sortset = setnewtypeleft(typeofsort);
			}
			else if (params.returnfunckey == 77) {
				sortset = setnewtyperight(typeofsort);
			}
		}
		
	}
}
void DataBaseInterface::searchbyrate() {
	TrainShow show;
	Searcher seeker;
	Sorter s;
	system("cls");
	cout << "Loading train's data...";
	vector<TrainData> train = base.getdata();
	string sortset = "<None>";
	TrainShow::ParamsforSearchMenu params = TrainShow::ParamsforSearchMenu();
	Sorter::SortType typeofsort = Sorter::SortType::NONE;
	while (!params.end) {
		params.mainline = " Type of sort: " + sortset + "\n Enter rate: " + params.searchstr;
		float rate = strtofloat(params.searchstr);
		params.trains = seeker.searchtrains(train, rate);
		s.sort(params.trains, typeofsort);

		show.ArrowSearchMenu(params, settings);

		if (params.returnkey != '\0') {
			if ((params.returnkey >= '0' && params.returnkey <= '9') || params.returnkey == '.') {
				if (params.searchstr.size() <= 255) {
					params.searchstr += params.returnkey;
				}
			}
		}
		if (params.returnfunckey != 0) {
			if (params.returnfunckey == 75) {
				sortset = setnewtypeleft(typeofsort);
			}
			else if (params.returnfunckey == 77) {
				sortset = setnewtyperight(typeofsort);
			}
		}
	}
}
void DataBaseInterface::searchbydate()
{
	TrainShow show;
	Searcher seeker;
	Sorter s;
	string background = "hhmmddmmyyyy";
	system("cls");
	cout << "Loading train's data...";
	vector<TrainData> train = base.getdata();
	string sortset = "<None>";
	TrainShow::ParamsforSearchMenu params = TrainShow::ParamsforSearchMenu();
	Sorter::SortType typeofsort = Sorter::SortType::NONE;
	while (!params.end) {
		string back = background;
		for (int i = 0; i < (int)params.searchstr.size(); i++) {
			back[i] = params.searchstr[i];
		}
		params.mainline = " Type of sort: " + sortset + "\nEnter date&time of departure: " + back.substr(0, 2) + ':' + back.substr(2, 2) + "	";
		params.mainline += back.substr(4, 2) + '/' + back.substr(6, 2) + '/' + back.substr(8, 4);
		Date date = stringtodate(params.searchstr);
		params.trains = seeker.searchtrains(train, date);
		s.sort(params.trains, typeofsort);
		show.ArrowSearchMenu(params, settings);

		if (params.returnkey != '\0') {
			if (params.searchstr.size() < 12) {
				params.searchstr += params.returnkey;
			}
		}
		if (params.returnfunckey != 0) {
			if (params.returnfunckey == 75) {
				sortset = setnewtypeleft(typeofsort);
			}
			else if (params.returnfunckey == 77) {
				sortset = setnewtyperight(typeofsort);
			}
		}
	}
}
