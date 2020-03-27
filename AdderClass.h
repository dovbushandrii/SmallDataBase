#pragma once
#include "TrainDataStruct.h"

class Adder {
public:
	void addtrain(TrainData& newtrain);
private:
	void addnumber(TrainData& newtrain);
	void addname(TrainData& newtrain);
	void adddepdestination(TrainData& newtrain);
	void addtype(TrainData& newtrain);
	void adddate(TrainData& newtrain);
	void addrate(TrainData& newtrain);
};