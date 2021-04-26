#include "Warehouse.h"

using namespace std;

Record& Warehouse::find(int index) {
	int size = mStorage.size();
	for (int i = 0; i < size; i++) {
		if (mStorage[i].index == index) {
			Record& temp = mStorage[i];
			return temp;
		}
	}
	Record* empty = new Record();
	Record& temp = *empty;
	return temp;
}
Record& Warehouse::find(string name) {
	int size = mStorage.size();
	for (int i = 0; i < size; i++) {
		if (mStorage[i].name== name) {
			Record& temp = mStorage[i];
			return temp;
		}
	}
	Record* empty = new Record();
	Record& temp = *empty;
	return temp;
}

void Warehouse::addRecord(Record record) {
	Record found = find(record.name);
	if (found.index != -1) found.count += record.count;
	else if (found.index == -1) mStorage.push_back(record);
}
int Warehouse::deleteRecord(Record record) {
	for (int i = 0; i < mStorage.size(); i++) {
		if (mStorage[i].name == record.name) {
			if (record.count >= mStorage[i].count) mStorage.erase(mStorage.begin() + i);
			else mStorage[i].count -= record.count;
			return 0;
		}
	}
	return -1;
}

int Warehouse::buy(TCHAR* name, int count) {
	char buff[30];
	size_t len = wcstombs_s(0, buff, name, wcslen(name));
	if (len > 0u)
		buff[len] = '\0';
	string nameStr = string(buff);

	Record& record = find(nameStr);
	if (record.index == -1) return -1; //No such record

	if (record.count >= count) {
		OrdersSpace::Order order;
		if (mOrders.empty()) order.setNumber(0);
		else order.setNumber(mOrders.back().getNumber() + 1);

		order.setPayload(record);
		order.setState("Primary");
		Record ordered(0, name, 0, count);
		deleteRecord(ordered);
		mOrders.push_back(order);
		OrdersSpace::launch(&mOrders.back());
		return order.getNumber();
	}
	else {
		return -2; //Not enough goods in warehouse
	}
}

vector<Record> Warehouse::get_all_of_type(int type) {
	vector<Record> result;
	int size = mStorage.size();
	for (int i = 0; i < size; i++) {
		if (mStorage[i].type == type) {
			result.push_back(mStorage[i]);
		}
	}
	return result;
}

OrdersSpace::Order Warehouse::getOrder(int orderNumber) {
	for (int i = 0; i < mOrders.size(); i++) {
		if (mOrders[i].getNumber() == orderNumber) {
			//lock order object, because "return mOrders[i]" calls copy constructor, which touches found object
			lock_guard<recursive_mutex> locker(*mOrders[i].mut);
			return mOrders[i];
		}
	}
	return OrdersSpace::Order();
}