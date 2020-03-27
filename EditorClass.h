#pragma once
#include "OnlineDataBase.h"

class Editor {
public:
	void Edit(OnlineDataBase& base);
	void Adding(OnlineDataBase& base);
	void ChangeTrain(OnlineDataBase& base);
	void SelectionDeleting(OnlineDataBase& base);
	void DeleteAll(OnlineDataBase& base);
};