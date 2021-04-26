#include "Order.h"

struct OrdersSpace::OrderStatesStruct {
    vector<string> OrderStatesStr;
    vector<TCHAR*> OrderStatesTCHAR;
} orderStatesStruct;

void OrdersSpace::init() {
    orderStatesStruct.OrderStatesStr.push_back("Preparing");
    orderStatesStruct.OrderStatesStr.push_back("WaitingForDeparture");
    orderStatesStruct.OrderStatesStr.push_back("OnTheWay");
    orderStatesStruct.OrderStatesStr.push_back("Arrived");

    //converting strings to TCHAR strings
    orderStatesStruct.OrderStatesTCHAR.resize(OrderStates::Size);
    for (int i = 0; i < OrderStates::Size; i++) {
        int len = orderStatesStruct.OrderStatesStr[i].size();
        orderStatesStruct.OrderStatesTCHAR[i] = new TCHAR[len];

        const char* orig = orderStatesStruct.OrderStatesStr[i].c_str();
        size_t converted_chars = 0;
        size_t new_size = strlen(orig) + 1;
        mbstowcs_s(&converted_chars, orderStatesStruct.OrderStatesTCHAR[i], new_size, orig, _TRUNCATE);
    }
}
void OrdersSpace::launch(Order* order) {
    thread thr(&work, order);
    thr.detach();
}
void OrdersSpace::work(Order* order) {
    order->setState(orderStatesStruct.OrderStatesStr[OrderStates::Preparing]);
    this_thread::sleep_for(std::chrono::seconds(10));

    order->setState(orderStatesStruct.OrderStatesStr[OrderStates::WaitingForDeparture]);
    this_thread::sleep_for(std::chrono::seconds(10));

    order->setState(orderStatesStruct.OrderStatesStr[OrderStates::OnTheWay]);
    this_thread::sleep_for(std::chrono::seconds(10));

    order->setState(orderStatesStruct.OrderStatesStr[OrderStates::Arrived]);
    this_thread::sleep_for(std::chrono::seconds(10));
}

OrdersSpace::Order::Order() : mNumber(-1), mut(new recursive_mutex){};
OrdersSpace::Order::Order(const Order &other) {
    lock_guard<recursive_mutex> locker(*other.mut);
    mState = other.getState();
    mPayload = other.getPayload();
    mNumber = other.getNumber();
    mut = new recursive_mutex;
}
OrdersSpace::Order::Order(int number, Record payload) {
    mNumber = number;
    mPayload = payload;
    mut = new recursive_mutex;
}

void OrdersSpace::Order::setNumber(int number) {
    mNumber = number;
}
int OrdersSpace::Order::getNumber() const {
    return mNumber;
}

void OrdersSpace::Order::setPayload(Record record) {
    mPayload = record;
}
Record OrdersSpace::Order::getPayload() const {
    return mPayload;
}

void OrdersSpace::Order::setState(string state) {
    lock_guard<recursive_mutex> locker(*mut);
    mState = state;
}
string OrdersSpace::Order::getState() const {
    return mState;
}
