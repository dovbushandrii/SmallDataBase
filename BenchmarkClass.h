#pragma once
#include "TrainDataStruct.h"
#include "OnlineDataBase.h"

class Benchmark {
public:
	void BenchmarkTest(string path);
	TrainData& CreateRandomTrain();
private:
	void Bench(OnlineDataBase& base, string path);
	OnlineDataBase& createdatabase(int N);
};