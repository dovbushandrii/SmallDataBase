#include <iostream>
#include "DatabaseClasses.h"
#include <time.h>

using namespace std;

void Demonstrator::Demo() {
	TrainShow show;
	OnlineDataBase demobase;
	Benchmark bench;
	system("cls");

	cout << "Hello user!\This is short demonstration for you!\n";
	cout << '\n';
	system("pause");
	system("cls");

	cout << "Firstly, let's have a look on the menu:\n";
	cout << "Train Search\nEditing\nSearch Settings\nDemo\nBenchmark\nExit\n";
	cout << "\nYou can go back/exit by pressing esc almost everywhere\n(except for entering rate of train and ID)\n";
	cout << '\n';
	system("pause");
	system("cls");

	cout << "For creating new train go:\n\nEditing->Add train\n";
	cout << "\nWe will create two trains for you:\n";
	TrainData newtrain = bench.CreateRandomTrain();
	demobase.addelement(newtrain);
	newtrain = bench.CreateRandomTrain();
	demobase.addelement(newtrain);
	demobase.setid(demobase.getdata());
	show.showtrain(demobase.getdata()[0]);
	cout << '\n';
	show.showtrain(demobase.getdata()[1]);
	cout << '\n';
	system("pause");
	system("cls");

	cout << "If you want to change train data, go:\nEditing->Change Train\n";
	cout << "\nEnter train ID for changing, if there wasn't such ID, no problem,\ntry again, or enter 0 for exiting change mode\n";
	cout << '\n';
	system("pause");
	system("cls");

	cout << "We've changed name of first train to Shevchenko,\nbut also it is optional to write name\n";
	demobase.getdata()[0].name = "Shevchenko";
	show.showtrain(demobase.getdata()[0]);
	cout << '\n';
	show.showtrain(demobase.getdata()[1]);
	cout << '\n';
	system("pause");
	system("cls");
	
	cout << "If you want to delete files:\n\nYou can delete one by one in:\nEdit->Selective data delete\n\n";
	cout << "You can delete all data in:\nEdit->Delete all data\n\n";
	system("pause");
	system("cls");

	cout << "In <Search Setting> you can change show params in search func.\n";
	cout << "For example, you can only left one <Yes> in Setting(F.e. name),\nand only name and ID will be shown in search mode\n\n";

	system("pause");
	system("cls");

	cout << "In search mode:\nTrain Search->Search by name(rate,date)\n\n";
	cout << "For searching just start to enter symbols(by name) or numbers(rate,date),\n";
	cout << "and search result will be updated as you entered of deleted sybmol(Backspace)\n\n";
	cout << "For exiting search just smash that ESC button on the top left of your keyboard!\n\n";

	system("pause");
	system("cls");

	cout << "The last feature is Benchmark.\nJust smash that option for benchmark\n";
	cout << "That option tests creating database on N random elements,\ntests writing&reading .txt and .bin-files\n";
	cout << "and tests all types of search on random-generated database";
	cout << "You can compare number of elements/bytes benchmarked with your friend!\n\n";

	system("pause");
	system("cls");

	cout << "After hitting EXIT in main menu, you will be asked:\n\n";
	cout << "Save changes ? (Enter - Yes; Esc - No)\n\n";
	cout << "If you hit <Yes> all changes will be saved, if <No> -> wont\n\n";

	system("pause");
	system("cls");

	cout << "So, thats it. Try on your own!)\n";

	system("pause");
	system("cls");

}