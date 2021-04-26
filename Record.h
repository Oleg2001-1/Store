#pragma once
#include <string>
#include <tchar.h>
using namespace std;

struct Record {
	int index;
	string name;
	int type;
	int count;

	Record();
	Record(int index, TCHAR* name, int type, int count);
};