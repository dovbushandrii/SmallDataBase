#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;


enum ShowOptions {
	SHOWN,
	NOTSHOWN
};
enum Type {
	INTER,
	SPEED,
	STANDART,
	INTERCITY
};
struct Date {
	Date() {
		day = month = year = hours = minutes = hours2 = minutes2 = 0;
	}
	int day;
	int month;
	int year;
	int hours;		//Время прибытия
	int minutes;
	int hours2;		//Время отправления
	int minutes2;
};
struct TrainData {
	TrainData() {
		id = 0;
		rate = 0;
		type = Type::INTER;
	}
	int id;
	string no;
	string name;
	string departurepoint;
	string destination;
	Type type;
	Date date;
	float rate;

};

class OnlineDataBase {
public:
	OnlineDataBase(){}
	void loaddata(vector<TrainData> load) {
		for (int i = 0; i < load.size(); i++) {
			OnlineBase.push_back(load[i]);
		}
	}
	void addelement(TrainData add) {
		OnlineBase.push_back(add);
	}
	void deletedata() {
		if (OnlineBase.size() > 0) {
			vector<TrainData> newbase;
			OnlineBase = newbase;
		}
	}
	void deleteelement(int i) {
		if (i > OnlineBase.size()) {
			throw exception("Индекс элемента для удаления больше кол-ва элементов базы");
		}
		else {
			vector<TrainData> newbase;
			for (int j = 0; j < i; j++) {
				newbase.push_back(OnlineBase[j]);
			}
			for (int j = i + 1; j < OnlineBase.size(); j++) {
				newbase.push_back(OnlineBase[j]);
			}
			OnlineBase = newbase;
		}

	}
	void setid(vector<TrainData>& Base) {
		for (int i = 0; i < Base.size(); i++) {
			Base[i].id = i + 1;
		}
	}
	vector<TrainData>& getdata() {
		return OnlineBase;
	}
	vector<TrainData> OnlineBase;
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
	ShowOptions settings[6];   // Настройки отобрыжения данных  в поиске (Номер, Название, Направление, Тип, Дата, Рейтинг)
	OnlineDataBase base;	   //Online база данных
	void Settings(); // done
	void Search(); 
	void searchbyname();
	void searchbyrate();
	void searchbydate();
};

class Editor {
public:
	void Edit(OnlineDataBase& base);
	void Adding(OnlineDataBase& base);
	void ChangeTrain(OnlineDataBase& base);
	void SelectionDeleting(OnlineDataBase& base);
	void DeleteAll(OnlineDataBase& base);
};

class TrainShow {
public:
	struct ParamsforSearchMenu {
		ParamsforSearchMenu() {
			end = false;
			line = 0;
			returnkey = '\0';
			searchstr = "";
			mainline = "";
		}
		bool end;
		int line;
		char returnkey;
		string searchstr;
		string mainline;
		vector<TrainData> trains;
	};
	struct ParamsforArrowMenu{
		ParamsforArrowMenu() {
			end = false;
			line = 0;
			returnkey = '\0';
		}
		bool end;
		int line;
		char returnkey;
		vector<string> lines;
	};
	void ArrowSearchMenu(TrainShow::ParamsforSearchMenu& params, ShowOptions settings[]);
	void ArrowsOnlyMenu(TrainShow::ParamsforArrowMenu& params);
	void traindatatooutstring(TrainData train, ShowOptions settings[]);
	void traindatatooutstring(TrainData train);
	void showtrain(TrainData train);
};

class Adder {
public:
	void addtrain(TrainData& newtrain); // done
private:
	void addnumber(TrainData& newtrain); //done
	void addname(TrainData& newtrain);  //done
	void adddepdestination(TrainData& newtrain); //done
	void addtype(TrainData& newtrain);  //done
	void adddate(TrainData& newtrain);  //done
	void addrate(TrainData& newtrain);  //done
};			// done,but needs more effitient solution

class Searcher {
public: 
	vector<TrainData> searchtrains(vector<TrainData> base,string name);
	vector<TrainData> searchtrains(vector<TrainData> base,float rate);
	vector<TrainData> searchtrains(vector<TrainData> base,Date date);
};		    // Done

class FileManager {
public:
	void StoringData(OnlineDataBase& base);
	void DownloadData(OnlineDataBase& base);
	void StoringData(OnlineDataBase& base, string path);
	void DownloadData(OnlineDataBase& base, string path);
	vector<TrainData> downloaddata(string path);
	vector<TrainData> downloaddatabin(string path);
	void uploaddata(OnlineDataBase base,string path);
	void uploaddatabin(OnlineDataBase base, string path);
};

class Random {
public:
	string randstr();
	int randbyte();
	Type randtype();
	float randrate();
	Date randdate();
};

class Benchmark {
public:
	void BenchmarkTest(string path);
	TrainData& CreateRandomTrain();
private: 
	void Bench(OnlineDataBase& base,string path);
	OnlineDataBase& createdatabase(int N);
};

class Demonstrator {
public:
	void Demo();
};






