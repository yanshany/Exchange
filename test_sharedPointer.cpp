#include "order.hpp"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

int main()
{

    vector<shared_ptr<Order>> orders;
    vector<shared_ptr<Order>> ordersPtr;
    orders.push_back(make_shared<Order>("A","AUDUSD",100,1.7));

    ordersPtr.push_back(orders[0]);
    cout << ordersPtr[0]->quantity << std::endl;
    ordersPtr[0]->quantity = 50;
    cout << orders[0]->quantity << std::endl;
    
    ordersPtr.clear();

    cout << orders[0]->quantity << std::endl;

/*
    vector<Order> orders;
    vector<shared_ptr<Order>> ordersPtr;
    orders.push_back(Order("A","AUDUSD",100,1.7));

    ordersPtr.push_back(make_shared<Order>(orders[0]));
    cout << ordersPtr[0]->quantity << std::endl;
    ordersPtr[0]->quantity = 50;
    cout << orders[0].quantity << std::endl;
    
    ordersPtr.clear();
*/
    return 0;
}