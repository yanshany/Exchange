#include "order.hpp"
#include "trade.hpp"
#include "parseLineToOrder.hpp"
#include "chooseCandidate.hpp"
#include "updateOpenOrder.hpp"
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
	vector<Trade> myTrade;
    vector<shared_ptr<Order>> openOrder;
    vector<shared_ptr<Order>> candidate;

	// read in orders from standard input
	while (getline(cin, s))
	{
		allOrder.push_back(parseLineToOrder(s, delimiter));
	}

	openOrder.push_back(make_shared<Order>(allOrder[0]));

	for (int i = 1; i != allOrder.size(); ++i)
	{
		newOrder = allOrder[i];
		if (newOrder.quantity > 0) // buy order
		{
			// find sell orders in order book matching instument and acceptable price
			// the order book copy is used in iteration of for loop. Because we change the size of openOrder in the for loop, openOrder can not be usd in the iteration of for loop
			for (int j = 0; j != openOrder.size(); ++j)
			{
				if (newOrder.instrument == openOrder[j]->instrument && openOrder[j]->quantity < 0 && openOrder[j]->price <= newOrder.price)
				{
					candidate.push_back(openOrder[j]);
				}
			}

			// cannot find matching order, add the new order in order book
			if (candidate.size() == 0)
				openOrder.push_back(make_shared<Order>(newOrder));
			else
			{
				// sort candidate according to price
                sort(candidate.begin(),candidate.end(),[](const shared_ptr<Order>& lhs, const shared_ptr<Order>& rhs)
                {
                        return lhs->price < rhs->price;
                });
				// matching new order with candidate in order book
				for (int k = 0; k != candidate.size(); ++k)
				{
					myTrade.push_back(Trade(newOrder.name, candidate[k]->name, newOrder.instrument, min(newOrder.quantity, -1 * candidate[k]->quantity), candidate[k]->price));
					if (newOrder.quantity < -1 * candidate[k]->quantity)
					{
						candidate[k]->quantity += newOrder.quantity;
						break;
					}
					else if (newOrder.quantity > -1 * candidate[k]->quantity)
					{
						newOrder.quantity += candidate[k]->quantity;
						candidate[k]->quantity = 0;
					}
					else
					{
						candidate[k]->quantity = 0;
						break;
					}	
				}
			}
			// clear variables
			candidate.clear();
		}
		if (newOrder.quantity < 0) // sell order
		{
			// find sell orders in order book matching instument and acceptable price
			for (int j = 0; j != openOrder.size(); ++j)
			{
				if (newOrder.instrument == openOrder[j]->instrument && openOrder[j]->quantity > 0 && openOrder[j]->price >= newOrder.price)
				{
					candidate.push_back(openOrder[j]);
				}
			}

			// cannot find matching order, add the new order in order book
			if (candidate.size() == 0)
				openOrder.push_back(make_shared<Order>(newOrder));
			else
			{
				// sort candidate according to price
                sort(candidate.begin(),candidate.end(),[](const shared_ptr<Order>& lhs, const shared_ptr<Order>& rhs)
                {
                        return lhs->price > rhs->price;
                });
				// matching new order with candidate in order book
				for (int k = 0; k != candidate.size(); ++k)
				{
					myTrade.push_back(Trade(candidate[k]->name, newOrder.name,newOrder.instrument, min(-1*newOrder.quantity, candidate[k]->quantity), candidate[k]->price));
					if (-1*newOrder.quantity < candidate[k]->quantity)
					{
						candidate[k]->quantity += newOrder.quantity;
						break;
					}	
					else if (-1*newOrder.quantity > candidate[k]->quantity)
					{
						newOrder.quantity += candidate[k]->quantity;
						candidate[k]->quantity = 0;
					}
					else
					{
						candidate[k]->quantity = 0;
						break;
					}	
				}
			}
			// clear variables
			candidate.clear();
		}
	}

	for (int i = 0; i != myTrade.size(); ++i)
	{
		myTrade[i].print();
	}

}
