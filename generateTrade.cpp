#include "order.hpp"
#include "trade.hpp"
#include "generateTrade.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

vector<shared_ptr<Trade>> generateTrade(Order newOrder, vector<shared_ptr<Order>> &openOrder, vector<shared_ptr<Trade>> myTrade)
{
    vector<shared_ptr<Order>> candidate;

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
            sort(candidate.begin(), candidate.end(), [](const shared_ptr<Order> &lhs, const shared_ptr<Order> &rhs) {
                return lhs->price < rhs->price;
            });
            // matching new order with candidate in order book
            for (int k = 0; k != candidate.size(); ++k)
            {
                myTrade.push_back(make_shared<Trade>(newOrder.name, candidate[k]->name, newOrder.instrument, min(newOrder.quantity, -1 * candidate[k]->quantity), candidate[k]->price));
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
            sort(candidate.begin(), candidate.end(), [](const shared_ptr<Order> &lhs, const shared_ptr<Order> &rhs) {
                return lhs->price > rhs->price;
            });
            // matching new order with candidate in order book
            for (int k = 0; k != candidate.size(); ++k)
            {
                myTrade.push_back(make_shared<Trade>(candidate[k]->name, newOrder.name, newOrder.instrument, min(-1 * newOrder.quantity, candidate[k]->quantity), candidate[k]->price));
                if (-1 * newOrder.quantity < candidate[k]->quantity)
                {
                    candidate[k]->quantity += newOrder.quantity;
                    break;
                }
                else if (-1 * newOrder.quantity > candidate[k]->quantity)
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
    return myTrade;
};