#include "updateOpenOrder.hpp"
#include "order.hpp"
#include <vector>

using namespace std;

vector<Order> updateOpenOrder(Order newOrder, vector<Order> openOrder, int ind)
{
// update the order book by comparing the size of the new order and the matched order, the matched order the ind'th order in the order book
    if (newOrder.quantity > 0) 
    {
        if (newOrder.quantity < -1 * openOrder[ind].quantity)
            openOrder[ind].quantity += newOrder.quantity;
        else if (newOrder.quantity > -1 * openOrder[ind].quantity)
        {
            openOrder.push_back(Order(newOrder.name, newOrder.instrument, newOrder.quantity + openOrder[ind].quantity, newOrder.price));
            openOrder.erase(openOrder.begin() + ind);
        }
        else
            openOrder.erase(openOrder.begin() + ind);
        return openOrder;
    }
    else
    {
        if (-1*newOrder.quantity < openOrder[ind].quantity)
            openOrder[ind].quantity += newOrder.quantity;
        else if (-1*newOrder.quantity > openOrder[ind].quantity)
        {
            openOrder.push_back(Order(newOrder.name, newOrder.instrument, newOrder.quantity + openOrder[ind].quantity, newOrder.price));
            openOrder.erase(openOrder.begin() + ind);
        }
        else
            openOrder.erase(openOrder.begin() + ind);
        return openOrder;
    }
};
