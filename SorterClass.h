#pragma once
#include "TrainDataStruct.h"
#include "functional"
#include <vector>
#include <iostream>

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
int getnumbfortraintype(TrainData train) {
	return train.type;
}
int getnumbfortrainumb1(TrainData train) {
	return (train.no[3]-'0');
}
int getnumbfortrainumb2(TrainData train) {
	return (train.no[2] - '0');
}
int getnumbfortrainumb3(TrainData train) {
	return (train.no[1] - '0');
}
int getnumbfortrainumb4(TrainData train) {
	return (train.no[0] - '0');
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
		TYPE,
		DATE,
		RATE
	};
	void sort(vector<TrainData>& base, SortType type) {
		switch (type) {
		case NUMBER:{
			radixsort(base);
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
		case TYPE: {
			countingsort(base, getnumbfortraintype);
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
	void radixsort(vector<TrainData>& base) {
		countingsort(base, getnumbfortrainumb1);
		countingsort(base, getnumbfortrainumb2);
		countingsort(base, getnumbfortrainumb3);
		countingsort(base, getnumbfortrainumb4);
	}
	void countingsort(vector<TrainData>& base, int getnumb(TrainData train)) {
		TrainData* output = new TrainData[(int)base.size()];
		int max = getMax(base, getnumb);
		int* count = new int[max + 1];
		for (int i = 0; i < (max + 1); i++) {
			count[i] = 0;
		}
		for (int i = 0; i < (int)base.size(); i++) {
			count[getnumb(base[i])]++;
		}
		for (int i = 1; i < max + 1; i++) {
			count[i] += count[i - 1];
		}
		for (int i = (int)base.size()-1; i >= 0; i--) {
			output[count[getnumb(base[i])]-1] = base[i];
			count[getnumb(base[i])]--;
		}
		for (int i = 0; i < (int)base.size(); i++) {
			base[i] = output[i]; 
		}
	}
	int getMax(vector<TrainData> base, int getnumb(TrainData train)) {
		int max = getnumb(base[0]);
		for (int i = 1; i < (int)base.size(); i++) {
			if (getnumb(base[i]) > max)
				max = getnumb(base[i]);
		}
		return max;
	}
	
};