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
enum SortBy {
	NUMBER,
	NAME,
	DEPARTUREPOINT,
	DESTINATION,
	TYPE,
	DATE,
	RATE
};
struct Date {
	int day;
	int month;
	int year;
	int hours;
	int minutes;
};
struct TrainData {
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
	void loaddata(vector<TrainData> load) {
		for (int i = 0; i < OnlineBase.size(); i++) {
			OnlineBase.push_back(load[i]);
		}
	}
	void addelement(TrainData add) {
		OnlineBase.push_back(add);
	}
	void deletedata() {
		for (int i = 0; i < OnlineBase.size(); i++) {
			OnlineBase.pop_back();
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
		setlocale(LC_ALL, "Russian");
	} // done
	void Menu(); // done
private:
	ShowOptions settings[6];   // Настройки отобрыжения данных  в поиске (Номер, Название, Направление, Тип, Дата, Рейтинг)
	OnlineDataBase base;
	void Edit(); // done
	void Adding(); 
	void Deleting(); 
	void Settings(); // done
	void Search(); 
	void Demo();
	void Benchmark();
	void traindatatooutstring(TrainData train); //done
};

class Adder {
public:
	void addnumber(TrainData& newtrain);
	void addname(TrainData& newtrain);
	void adddepdestination(TrainData& newtrain);
	void addtype(TrainData& newtrain);
	void adddate(TrainData& newtrain);
	void addrate(TrainData& newtrain);
};

class Searcher {
public: 
	vector<TrainData> searchtrains(vector<TrainData>& base);
	vector<TrainData> searchtrains(vector<TrainData>& base,string name);
	vector<TrainData> searchtrains(vector<TrainData>& base,float rate);
	vector<TrainData> searchtrains(vector<TrainData>& base,Date date);
	void sortby(vector<TrainData>& SearchResult, SortBy filter);
};

class FileManager {

};

class Benchmark {

};

class Demonstrator {

};

