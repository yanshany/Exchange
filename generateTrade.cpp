#include "order.hpp"
#include "trade.hpp"
#include "generateTrade.hpp"
#include <algorithm>
#include <memory>

void generateTrade(Order &newOrder, std::vector<std::shared_ptr<Order>> &openOrder, std::vector<std::shared_ptr<Trade>> &myTrade)
{
    std::vector<std::shared_ptr<Order>> candidate;

    if (newOrder.quantity() > 0) // buy order
    {
        // find sell orders in order book matching instument and acceptable price
        for (int j = 0; j != openOrder.size(); ++j)
        {
            if (newOrder.instrument() == openOrder[j]->instrument() && openOrder[j]->quantity() < 0 && openOrder[j]->price() <= newOrder.price())
            {
                candidate.push_back(openOrder[j]);
            }
        }

        // cannot find matching order, add the new order in order book
        if (candidate.size() == 0)
            openOrder.push_back(std::make_shared<Order>(newOrder));
        else
        {
            // sort candidates according to prices
            std::sort(candidate.begin(), candidate.end(), [](const std::shared_ptr<Order> &lhs, const std::shared_ptr<Order> &rhs) {
                return lhs->price() < rhs->price();
            });
            // matching new order with candidates in order book
            for (int k = 0; k != candidate.size(); ++k)
            {
                myTrade.push_back(std::make_shared<Trade>(newOrder.name(), candidate[k]->name(), newOrder.instrument(), std::min(newOrder.quantity(), -1 * candidate[k]->quantity()), candidate[k]->price()));
                if (newOrder.quantity() < -1 * candidate[k]->quantity())
                {
                    candidate[k]->quantity(candidate[k]->quantity() + newOrder.quantity());
                    break;
                }
                else if (newOrder.quantity() > -1 * candidate[k]->quantity())
                {
                    newOrder.quantity(newOrder.quantity() + candidate[k]->quantity());
                    candidate[k]->quantity(0);
                }
                else
                {
                    candidate[k]->quantity(0);
                    break;
                }
            }
            candidate.erase(std::remove_if(candidate.begin(),candidate.end(),[](const auto &p){return p->quantity() == 0;}),candidate.end());
        }
    }

    if (newOrder.quantity() < 0) // sell order
    {
        // find buy orders in order book matching instument and acceptable price
        for (int j = 0; j != openOrder.size(); ++j)
        {
            if (newOrder.instrument() == openOrder[j]->instrument() && openOrder[j]->quantity() > 0 && openOrder[j]->price() >= newOrder.price())
            {
                candidate.push_back(openOrder[j]);
            }
        }

        // cannot find matching order, add the new order in order book
        if (candidate.size() == 0)
            openOrder.push_back(std::make_shared<Order>(newOrder));
        else
        {
            // sort candidates according to prices
            std::sort(candidate.begin(), candidate.end(), [](const std::shared_ptr<Order> &lhs, const std::shared_ptr<Order> &rhs) {
                return lhs->price() > rhs->price();
            });
            // matching new order with candidates in order book
            for (int k = 0; k != candidate.size(); ++k)
            {
                myTrade.push_back(std::make_shared<Trade>(candidate[k]->name(), newOrder.name(), newOrder.instrument(), std::min(-1 * newOrder.quantity(), candidate[k]->quantity()), candidate[k]->price()));
                if (-1 * newOrder.quantity() < candidate[k]->quantity())
                {
                    candidate[k]->quantity(candidate[k]->quantity() + newOrder.quantity());
                    break;
                }
                else if (-1 * newOrder.quantity() > candidate[k]->quantity())
                {
                    newOrder.quantity(newOrder.quantity() + candidate[k]->quantity());
                    candidate[k]->quantity(0);
                }
                else
                {
                    candidate[k]->quantity(0);
                    break;
                }
            }
            candidate.erase(std::remove_if(candidate.begin(),candidate.end(),[](const auto &p){return p->quantity() == 0;}),candidate.end());
        }
    }
};
