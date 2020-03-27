#pragma once
#include "TrainDataStruct.h"
#include "functional"
#include <vector>

using namespace std;

bool numbercompar(TrainData a, TrainData b) {
	return (a.no > b.no) ? true : false;
}
bool namecompar(TrainData a, TrainData b) {
	return (a.name > b.name) ? true : false;
}
bool deppcompar(TrainData a, TrainData b) {
	return (a.departurepoint > b.departurepoint) ? true : false;
}
bool despcompar(TrainData a, TrainData b) {
	return (a.destination > b.destination) ? true : false;
}
bool atimecompar(TrainData a, TrainData b) {
	if (a.date.hours > b.date.hours) return true;
	else if (a.date.hours == b.date.hours) {
		if (a.date.minutes > b.date.minutes) return true;
		else return false;
	}
	else return false;
}
bool dtimecompar(TrainData a, TrainData b) {
	if (a.date.hours2 > b.date.hours2) return true;
	else if (a.date.hours2 == b.date.hours2) {
		if (a.date.minutes2 > b.date.minutes2) return true;
		else return false;
	}
	else return false;
}
bool datecompar(TrainData a, TrainData b) {
	if (a.date.year > b.date.year) return true;
	else if (a.date.year == b.date.year) {
		if (a.date.month > b.date.month) return true;
		else if (a.date.month == b.date.month) {
			if (a.date.day > b.date.day) return true;
			else return false;
		}
		else return false;
	}
	else return false;
}
bool ratecompar(TrainData a, TrainData b) {
	return (a.rate > b.rate) ? true : false;
}

class Sorter {
public:
	enum SortType {
		NONE,
		NUMBER,
		NAME,
		DEPARTUREPOINT,
		DESTINATIONPOINT,
		ARRIVALTIME,
		DEPARTURETIME,
		DATE,
		RATE
	};
	void sort(vector<TrainData>& base, SortType type) {
		switch (type) {
		case NUMBER:{
			privatesort(base,numbercompar);
			break;
		}
		case NAME:{
			privatesort(base, namecompar);
			break;
		}
		case DEPARTUREPOINT: {
			privatesort(base, deppcompar);
			break;
		}
		case DESTINATIONPOINT: {
			privatesort(base, despcompar);
			break;
		}
		case ARRIVALTIME: {
			privatesort(base, atimecompar);
			break;
		}
		case DEPARTURETIME: {
			privatesort(base, dtimecompar);
			break;
		}
		case DATE: {
			privatesort(base, datecompar);
			break;
		}
		case RATE: {
			privatesort(base, ratecompar);
			break;
		}
		default: break;
		}
	}
private:
	void privatesort(vector<TrainData>& base, function<bool (TrainData a, TrainData b)> comp) {
		recursivequick(base, 0, (int)base.size() - 1, comp);
	}
	void recursivequick(vector<TrainData>& list, int minindex, int maxindex, function<bool(TrainData a, TrainData b)> comp) {
		int i, j;
		TrainData p;
		if (minindex >= maxindex) {
			return;
		}
		i = minindex - 1;
		j = maxindex + 1;
		p = list[(i+j)/2];
		while (1)
		{
			while (comp(p, list[++i]));
			while (comp(list[--j], p));
			if (i >= j) {
				break;
			}
			swap(list, i, j);
		}
		recursivequick(list, minindex, j , comp);
		recursivequick(list, j + 1, maxindex , comp);
	}
	void swap(vector<TrainData>& base, int i, int j) {
		TrainData c = base[i];
		base[i] = base[j];
		base[j] = c;
	}
};