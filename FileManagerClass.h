#pragma once
#include "OnlineDataBase.h"
#include <string>
#include <vector>

using namespace std;

class FileManager {
public:
	void StoringData(OnlineDataBase& base);
	void DownloadData(OnlineDataBase& base);
	void StoringData(OnlineDataBase& base, string path);
	void DownloadData(OnlineDataBase& base, string path);
	vector<TrainData> downloaddata(string path);
	vector<TrainData> downloaddatabin(string path);
	void uploaddata(OnlineDataBase base, string path);
	void uploaddatabin(OnlineDataBase base, string path);
};