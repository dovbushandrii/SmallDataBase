#include <string>
#include "DataBaseClasses.h"

using namespace std;

float strtofloat(string number) {
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
	if ((number[0] == '0' && number[1] == '.') || number[0] == '.') {
		res *= 10;
	}
	return res;
}
Date stringtodate(string date) {
	Date newdate;
	int year = 0;
	int month = 0;
	int day = 0;
	int hours = 0;
	int minutes = 0;
	int size = date.size();
	for (int i = 0; i < (13 - size); i++) {
		date += '0';
	}

	for (int i = 11; i > 7; i--) {
		year += (date[i] - '0') * pow(10, (11 - i));
	}
	for (int i = 7; i > 5; i--) {
		month += (date[i] - '0') * pow(10, (7 - i));
	}
	for (int i = 5; i > 3; i--) {
		day += (date[i] - '0') * pow(10, (5 - i));
	}
	for (int i = 3; i > 1; i--) {
		minutes += (date[i] - '0') * pow(10, (3 - i));
	}
	for (int i = 1; i >= 0; i--) {
		hours += (date[i] - '0') * pow(10, (1 - i));
	}
	newdate.year = year;
	newdate.month = month;
	newdate.day = day;
	newdate.hours2 = hours;
	newdate.minutes2 = minutes;
	newdate.hours = hours;
	newdate.minutes = minutes;
	return newdate;
}