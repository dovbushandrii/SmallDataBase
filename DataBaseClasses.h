#pragma once
#include <vector>
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
	TIME,
	RATE
};
struct TrainData {
	int no;
	string name;
	string departurepoint;
	string destination;
	Type type;
	float rate;

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

	void Edit();
	void Settings(); // done
	void Search();
	void Demo();
	void Benchmark();
};

class Searcher {
public: 
	vector<TrainData> searchtrains(vector<TrainData>& base);
	void sortby(vector<TrainData>& SearchResult, SortBy filter);
};

class FileManager {

};

class Benchmark {

};

class Demonstrator {

};

class OnlineDataBase {
public:
	void loaddata(vector<TrainData> load) {
		for (int i = 0; i < OnlineBase.size(); i++) {
			OnlineBase.push_back(load[i]);
		}
	}
	void deletedata() {
		for (int i = 0; i < OnlineBase.size(); i++) {
			OnlineBase.pop_back();
		}
	}
	vector<TrainData>& getdata() {
		return OnlineBase;
	}
private:
	vector<TrainData> OnlineBase;
};
