#pragma once
#include <vector>
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

class DataBaseInterface {
public:
	DataBaseInterface() {
		for (int i = 0; i < 6; i++) {
			settings[i] = ShowOptions::SHOWN;
		}
		setlocale(LC_ALL, "Russian");
	} // done
	void Menu(); // done
	void Settings(); // done
	void Search();
	void Demo();
	void Benchmark();
private:
	ShowOptions settings[6];   // Настройки отобрыжения данных  в поиске (Номер, Название, Направление, Тип, Дата, Рейтинг)
};

class Searcher {
public: vector < string > searchtrains(int& No, string& Name, string& Destination, Type& type, string& Time, float& Rate);
};

class FileManager {

};


class Benchmark {

};

class Demonstrator {

};

struct TrainData {
	int no;
	string name;
	string departurepoint;
	string destination;
	Type type;
	float rate;
	
};

class OnlineDataBase {

};