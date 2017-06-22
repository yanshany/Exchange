#include "order.hpp"
#include "trade.hpp"
#include "parseLineToOrder.hpp"
#include "generateTrade.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

int main()
{
	string s;
	string delimiter = ":";
	Order newOrder = Order();
	vector<Order> allOrder;
	vector<shared_ptr<Trade>> myTrade;
    vector<shared_ptr<Order>> openOrder;

	// read in orders from standard input
	while (getline(cin, s))
	{
		allOrder.push_back(parseLineToOrder(s, delimiter));
	}

	openOrder.push_back(make_shared<Order>(allOrder[0]));
	for (int i = 1; i != allOrder.size(); ++i)
	{
		newOrder = allOrder[i];
		myTrade = generateTrade(newOrder,openOrder,myTrade);
	}

	for (int i = 0; i != myTrade.size(); ++i)
	{
		myTrade[i]->print();
	}

}
