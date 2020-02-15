#include <iostream>
#include <string>
#include "DataBaseClasses.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

TrainData& Benchmark::CreateRandomTrain() {
	Random rand;
	TrainData* newtrain = new TrainData();
	(*newtrain).id = rand.randbyte();
	for (int i = 0; i < 4; i++) {
		(*newtrain).no += (rand.randbyte() + '0');
	}
	(*newtrain).name = rand.randstr();
	(*newtrain).departurepoint = rand.randstr();
	(*newtrain).destination = rand.randstr();
	(*newtrain).type = rand.randtype();
	(*newtrain).rate = rand.randrate();
	(*newtrain).date = rand.randdate();
	return *newtrain;
}

void Benchmark::BenchmarkTest(string path) {
	system("cls");
	cout << "Benchmark for " << path << " files running...\n\n";
	float N = 10;
	auto start = high_resolution_clock::now();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);
	auto startcreating = high_resolution_clock::now();
	auto endcreating = high_resolution_clock::now();
	auto durationcreating = duration_cast<milliseconds>(endcreating - startcreating);
	while (duration.count()+ durationcreating.count() < 1000) {

		startcreating = high_resolution_clock::now();
		OnlineDataBase newbase = this->createdatabase((int)N);
		endcreating = high_resolution_clock::now();

		durationcreating = duration_cast<milliseconds>(endcreating - startcreating);

		start = high_resolution_clock::now();
		long int sizeofbase = (newbase.getdata().size()) * sizeof(TrainData);
		this->Bench(newbase,path);
		end = high_resolution_clock::now();
		duration = duration_cast<milliseconds>(end - start);
		cout << "Number of elements: " << N << endl;
		cout << "Size: " << sizeofbase << " bytes\n";
		cout << "Time for write&read&search: " << duration.count() << " milliseconds\n";
		cout << "Time for creating: " << durationcreating.count() << " milliseconds\n\n";
		N *= 2;
	}
	float N_10 = N;
	int i = 1;
	while (duration.count()+ durationcreating.count() < 10000) {

		startcreating = high_resolution_clock::now();
		OnlineDataBase newbase = this->createdatabase((int)N);
		endcreating = high_resolution_clock::now();

		durationcreating = duration_cast<milliseconds>(endcreating - startcreating);

		start = high_resolution_clock::now();
		long int sizeofbase = (newbase.getdata().size()) * sizeof(TrainData);
		try {
			this->Bench(newbase,path);
		}
		catch (exception & ex) {
			cout << ex.what() << endl;
			system("pause");
		}
		end = high_resolution_clock::now();
		duration = duration_cast<milliseconds>(end - start);
		cout << "Number of elements: " << N << endl;
		cout << "Size: " << sizeofbase << " bytes\n";
		cout << "Time for write&read&search: " << duration.count() << " milliseconds\n";
		cout << "Time for creating: " << durationcreating.count() << " milliseconds\n\n";
		i++;
		N = N_10*i;
	}
	cout << "Results: " << (int)((N-N_10) / (duration.count()+ durationcreating.count()) * 10000) << " elements,\n";
	cout << "and " << (int)((N-N_10) * sizeof(TrainData) / (duration.count() + durationcreating.count()) * 10000) << " bytes is fully tested in 10 sec\n";
	system("pause");
	char pathcopy[255];
	path = "Bench" + path;
	strncpy_s(pathcopy, path.c_str(), 250);
	remove(pathcopy);
}

OnlineDataBase& Benchmark::createdatabase(int n){
	OnlineDataBase* newbase = new OnlineDataBase();
	for (int i = 0; i < n; i++) {
		newbase->addelement(this->CreateRandomTrain());
	}
	return *newbase;
}

void Benchmark::Bench(OnlineDataBase& base,string path) {
	FileManager fim;
	Searcher search;
	Random rand;
	int startsize = base.getdata().size();
	search.searchtrains(base.getdata(), rand.randstr());
	search.searchtrains(base.getdata(), rand.randrate());
	search.searchtrains(base.getdata(), rand.randdate());
	if (path == ".bin") {
		fim.uploaddatabin(base, "Bench" + path);
		base.deletedata();
		base.loaddata(fim.downloaddatabin("Bench" + path));
	}
	else if (path == ".txt") {
		fim.uploaddata(base, "Bench" + path);
		base.deletedata();
		base.loaddata(fim.downloaddata("Bench" + path));
	}
	else { throw exception("Inapropriate file type"); }
	int endsize = base.getdata().size();
	if (startsize != endsize) {
		throw  exception("Number of upload files are not equal to download files(");
	}
}
