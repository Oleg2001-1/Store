#include "Record.h"
using namespace std;

Record::Record() : index(-1) {};
Record::Record(int index, TCHAR* name, int type, int count) {
	this->index = index;

	//Converting TCHAR string to normal string
	char buff[30];
	size_t len = wcstombs_s(0, buff, name, wcslen(name));
	if (len > 0u)
		buff[len] = '\0';
	this->name = string(buff);

	this->type = type;
	this->count = count;
}