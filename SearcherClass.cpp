#include <iostream>
#include <string>
#include "SearcherClass.h"

using namespace std;

bool IsThereFragment(TrainData train,string frag) {
	string namepart = "";
	if (train.name.size() >= frag.size()) {
		for (int i = 0; i < train.name.size() - frag.size() + 1; i++) {
			namepart = train.name.substr( i, frag.size());
			if (namepart == frag) return true;
		}
	}
	return false;
}
bool IsDateBigger(TrainData train, Date date) {
	if (train.date.hours2 >= date.hours) {
		if (train.date.minutes2 >= date.minutes || train.date.hours2 > date.hours) {
			if (train.date.year > date.year) {
				return true;
			}
			else if (train.date.year == date.year) {
				if (train.date.month > date.month) {
					return true;
				}
				else if (train.date.month == date.month) {
					if (train.date.day > date.day) {
						return true;
					}
					else if (train.date.day == date.day) {
						return true;
					}
				}
			}
		}
	}
	
	return false;
}
		
vector<TrainData> Searcher::searchtrains(vector<TrainData> base, string frag) {
	vector<TrainData> newtrains;
	for (int i = 0; i < base.size(); i++) {
		if (IsThereFragment(base[i], frag)) {
			newtrains.push_back(base[i]);
		}
	}
	return newtrains;
}

vector<TrainData> Searcher::searchtrains(vector<TrainData> base, float rate) {
	vector<TrainData> newtrains;
	for (int i = 0; i < base.size(); i++) {
		if (base[i].rate>=rate) {
			newtrains.push_back(base[i]);
		}
	}
	return newtrains;
}

vector<TrainData> Searcher::searchtrains(vector<TrainData> base, Date date) {
	vector<TrainData> newtrains;
	for (int i = 0; i < base.size(); i++) {
		if (IsDateBigger(base[i], date)) {
			newtrains.push_back(base[i]);
		}
	}
	return newtrains;
}
