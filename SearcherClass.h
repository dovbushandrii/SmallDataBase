#pragma once
#include <vector>
#include <string>
#include "TrainDataStruct.h"

class Searcher {
public:
	vector<TrainData> searchtrains(vector<TrainData> base, string name);
	vector<TrainData> searchtrains(vector<TrainData> base, float rate);
	vector<TrainData> searchtrains(vector<TrainData> base, Date date);
};