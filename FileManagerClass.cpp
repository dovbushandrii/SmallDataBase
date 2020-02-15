#include <string>
#include <conio.h>
#include "DataBaseClasses.h"
#include <fstream>
#include <cstring>

using namespace std;

float stringtofloat(string number) {
	int point = 0;
	float res = 0;
	for (int i = number.size() - 1; i >= 0; i--) {
		if (number[i] == '.') {
			point = number.size() - i;
		}
		else {
			res += (number[i] - '0') * pow(10, number.size() - i - 1);
		}
	}
	res = res / pow(10, point);
	if (number[0] == '0' || number[0] == '.') {
		res *= 10;
	}
	return res;
}

void FileManager::uploaddata(OnlineDataBase base, string path) {
	ofstream fout;
	char pathcopy[255];
	strncpy_s(pathcopy, path.c_str(), 250);
	remove(pathcopy);
	fout.open(path, ofstream::app);
	if (!fout.is_open()) {
		throw exception("File opening fail!");
	}
	vector<TrainData> b = base.getdata();
	/*Порядок записи: айди,номер,название,пункт отправления/прибытия, тип поезда, 
	  дата прибытия на станцию(день,месяц,год), время прибытия на станцию(час,минуты), время
	   отправления, рейтинг*/
	for (int i = 0; i < b.size(); i++) {
		fout << b[i].id << '\t';
		fout << b[i].no << '\t' << b[i].name << '\t';
		fout << b[i].departurepoint << '\t' << b[i].destination << '\t';
		fout << b[i].type << '\t';
		fout << b[i].date.day << '\t' << b[i].date.month << '\t' <<b[i].date.year << '\t';
		fout << b[i].date.hours << '\t' << b[i].date.minutes << '\t';
		fout << b[i].date.hours2 << '\t' << b[i].date.minutes2 << '\t';
		fout << b[i].rate << '\n';
	}
	fout.close();
}
void FileManager::uploaddatabin(OnlineDataBase base, string path) {
	ofstream fout;
	char pathcopy[255];
	strncpy_s(pathcopy, path.c_str(), 250);
	remove(pathcopy);
	fout.open(path, ios_base::app | ios_base::binary);
	if (!fout.is_open()) {
		throw exception("File opening fail!");
	}
	vector<TrainData> b = base.getdata();
	long long int length = b.size();
	fout.write((char*)&length, sizeof(long long int));
	
	for (int i = 0; i < b.size(); i++) {
		TrainData* uploadtrain = new TrainData();
		int size = (int)sizeof(b[i]);
		*uploadtrain = b[i];
		fout.write((char*)&size, sizeof(int));
		fout.write((char*)uploadtrain, size);
	}

	fout.close();
}

vector<TrainData> FileManager::downloaddata(string path) {
	vector<TrainData> res;
	ifstream fin;
	fin.open(path);
	if (!fin.is_open()) {
		throw exception("File opening fail!");
	}
	bool end = false;
	while (!end) {
		TrainData newtrain;
		newtrain.date = Date();
		string train;
		getline(fin, train);
		if (train.size() < 2) {
			end = !end;
		}
		else {
			string idstr;
			int i = 0;
			for (; train[i] != '\t' ; i++) {
				idstr += train[i];
			}
			i++;
			// Считываю номер
			newtrain.no = train.substr(i, 4);
			i += 5;
			// Считываю название
			while (train[i] != '\t') {
				newtrain.name += train[i];
				i++;
			}
			i++;
			// Считываю пункт отправления
			while (train[i] != '\t') {
				newtrain.departurepoint += train[i];
				i++;
			}
			i++;
			// Считываю пункт назначения
			while (train[i] != '\t') {
				newtrain.destination += train[i];
				i++;
			}
			i++;
			// Считываю тип поезда
			int type = train[i] - '0';
			switch (type) {
			case 0: newtrain.type = Type::INTER; break;
			case 1: newtrain.type = Type::SPEED; break;
			case 2: newtrain.type = Type::STANDART; break;
			case 3: newtrain.type = Type::INTERCITY; break;
			}
			i += 2;
			// Считываю дату и время
			for (int j = 0; train[i] != '\t'; j++) {
				newtrain.date.day = newtrain.date.day * 10 + (train[i] - '0');
				i++;
			}
			i++;
			for (int j = 0; train[i] != '\t'; j++) {
				newtrain.date.month = newtrain.date.month * 10 + (train[i] - '0');
				i++;
			}
			i++;
			for (int j = 0; train[i] != '\t'; j++) {
				newtrain.date.year = newtrain.date.year * 10;
				newtrain.date.year += (train[i] - '0');
				i++;
			}
			i++;
			for (int j = 0; train[i] != '\t'; j++) {
				newtrain.date.hours = newtrain.date.hours * 10 + (train[i] - '0');
				i++;
			}
			i++;
			for (int j = 0; train[i] != '\t'; j++) {
				newtrain.date.minutes = newtrain.date.minutes * 10 + (train[i] - '0');
				i++;
			}
			i++;
			for (int j = 0; train[i] != '\t'; j++) {
				newtrain.date.hours2 = newtrain.date.hours2 * 10 + (train[i] - '0');
				i++;
			}
			i++;
			for (int j = 0; train[i] != '\t'; j++) {
				newtrain.date.minutes2 = newtrain.date.minutes2 * 10 + (train[i] - '0');
				i++;
			}
			// Считываю рейтинг
			i++;
			string rate;
			for (; i < train.size(); i++) {
				rate += train[i];
			}
			newtrain.rate = stringtofloat(rate);
			res.push_back(newtrain);
		}
	}
	fin.close();
	OnlineDataBase b;
	b.setid(res);
	return res;
}
vector<TrainData> FileManager::downloaddatabin(string path) {
	vector<TrainData> res;
	ifstream fin;
	fin.open(path, ios_base::binary);
	if (!fin.is_open()) {
		throw exception("No such file in directory!\nTrying to open .txt-file\n");
	}
	long long int length = 0;
	fin.read((char*)&length, sizeof(long long int));
	int size = 0;
	for (int i = 0;i <length;i++) {
		TrainData* newtrain = new TrainData();
		fin.read((char*)&size, sizeof(int));
		fin.read((char*)newtrain, size);
		TrainData newcopy = *newtrain;
		res.push_back(newcopy);
	}

	fin.close();
	OnlineDataBase b;
	b.setid(res);
	return res;
}

void FileManager::StoringData(OnlineDataBase& base) {
	system("cls");
	cout << "Save changes?(Enter - Yes;Esc - No)";
	char h = _getch();
	if (h == 13) {
		try {
			this->uploaddatabin(base, "Base.bin");
			this->uploaddata(base, "Base.txt");
		}
		catch (exception & ex) {
			cout << ex.what() << endl;
			system("pause");
		}
	}
}
void FileManager::StoringData(OnlineDataBase& base, string path) {
	try {

		this->uploaddatabin(base, path + ".bin");
		this->uploaddata(base, path + ".txt");
	}
	catch (exception & ex) {
		cout << ex.what() << endl;
		system("pause");
	}
}
void FileManager::DownloadData(OnlineDataBase& base) {
	system("cls");
	cout << "Loading train's data...";
	try {
		base.loaddata(this->downloaddatabin("Base.bin"));
		if (base.getdata().size() < 1) {
			throw exception("");
		}
	}
	catch (exception & ex){
		try {
			base.loaddata(this->downloaddata("Base.txt"));
			this->uploaddatabin(base, "Base.bin");
		}
		catch (exception & ex) {
			cout << ex.what();
			cout << "Nothing happened...\nCreating new one!\n";
			system("pause");
		}
	}
}
void FileManager::DownloadData(OnlineDataBase& base, string path){
		base.loaddata(this->downloaddatabin(path+".bin"));
		base.loaddata(this->downloaddata(path+".txt"));
}

