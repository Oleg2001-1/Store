#pragma once
#include "Record.h"
#include <ctime>
#include <time.h>
#include <thread>
#include <tchar.h>
#include <vector>
#include <Windows.h>
#include <mutex>
#include <future>
using namespace std;

namespace OrdersSpace {

	//All possible order states
	enum OrderStates {
		Preparing, WaitingForDeparture, OnTheWay, Arrived, Size
	};

	class Order {
	private:
		int mNumber;
		Record mPayload; //What is ordered
		string mState;


	public:
		Order();
		Order(const Order& other);
		Order(int number, Record payload);

		recursive_mutex* mut;

		void setPayload(Record record);
		Record getPayload() const;

		string getState() const;
		void setState(string state);

		void setNumber(int number);
		int getNumber() const;
	};

	void init(); //Prepare vector of TCHAR strings, containing order states
	void launch(Order* order); //launch new thread, with work function inside
	void work(Order* order); //Change order states every 10 seconds

	extern struct OrderStatesStruct; //extern is needed to avoid compilation error
}
