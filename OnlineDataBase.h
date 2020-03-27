#pragma once
#include "TrainDataStruct.h"
#include <vector>

using namespace std;

class OnlineDataBase {
public:
	OnlineDataBase() {}
	void loaddata(vector<TrainData> load) {
		for (int i = 0; i < (int)load.size(); i++) {
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
		if (i > (int)OnlineBase.size()) {
			throw exception("Индекс элемента для удаления больше кол-ва элементов базы");
		}
		else {
			OnlineBase.erase(OnlineBase.begin() + i);
		}

	}
	void setid(vector<TrainData>& Base) {
		for (int i = 0; i < (int)Base.size(); i++) {
			Base[i].id = i + 1;
		}
	}
	vector<TrainData>& getdata() {
		return OnlineBase;
	}
	vector<TrainData> OnlineBase;
};
