#pragma once
#include <string>
using namespace std;

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
	int hours;		//����� ��������
	int minutes;
	int hours2;		//����� �����������
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