#pragma once
#include "TrainDataStruct.h"
#include <string>

using namespace std;

class Random {
public:
	string randstr();
	int randbyte();
	Type randtype();
	float randrate();
	Date randdate();
};