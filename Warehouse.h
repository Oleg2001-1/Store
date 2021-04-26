#pragma once
#include <vector>
#include <string>
#include "Order.h"
using namespace std;
class Warehouse {
private:
	vector<Record> mStorage;
	vector<OrdersSpace::Order> mOrders;

	Record& find(int index);
	Record& find(string name);

public:

	vector<Record> get_all_of_type(int type);

	void addRecord(Record record);
	int deleteRecord(Record record);

	int buy(TCHAR* name, int count);

	OrdersSpace::Order getOrder(int orderNumber);
};
