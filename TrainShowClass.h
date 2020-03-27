#pragma once
#include <vector>
#include <string>
#include "TrainDataStruct.h"
#include "DataBaseInterfaceClass.h"

using namespace std;

class TrainShow {
public:
	struct ParamsforSearchMenu {
		ParamsforSearchMenu() {
			end = false;
			line = 0;
			returnkey = '\0';
			returnfunckey = 0;
			searchstr = "";
			mainline = "";
		}
		bool end;
		int line;
		char returnkey;
		int returnfunckey;
		string searchstr;
		string mainline;
		vector<TrainData> trains;
	};
	struct ParamsforArrowMenu {
		ParamsforArrowMenu() {
			end = false;
			line = 0;
			returnkey = '\0';
		}
		bool end;
		int line;
		char returnkey;
		vector<string> lines;
	};
	void ArrowSearchMenu(TrainShow::ParamsforSearchMenu& params, ShowOptions settings[]);
	void ArrowsOnlyMenu(TrainShow::ParamsforArrowMenu& params);
	void traindatatooutstring(TrainData train, ShowOptions settings[]);
	void traindatatooutstring(TrainData train);
	void showtrain(TrainData train);
private:
	//void showlist(vector<TrainData> trains, string mainline, int line, ShowOptions settings[]);
};