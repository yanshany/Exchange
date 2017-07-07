#include "order.hpp"
#include "trade.hpp"
#include "generateTrade.hpp"
#include <algorithm>
#include <memory>

void generateTrade(order& newOrder, std::vector<std::shared_ptr<order>>& openOrder, std::vector<trade>& myTrade)
{
    std::vector<std::shared_ptr<order>> candidate;

    if (newOrder.quantity() > 0) // buy order
    {
        // find sell orders in order book matching instument and acceptable price
        for (std::vector<std::shared_ptr<order>>::iterator j = openOrder.begin(); j != openOrder.end(); ++j)
        {
            if (newOrder.instrument() == (*j)->instrument() && (*j)->quantity() < 0 && (*j)->price() <= newOrder.price())
            {
                candidate.push_back(*j);
            }
        }

        // cannot find matching order, add the new order in order book
        if (candidate.size() == 0)
            openOrder.push_back(std::make_shared<order>(newOrder));
        else
        {
            // sort candidates according to prices
            std::stable_sort(candidate.begin(), candidate.end(), [](const std::shared_ptr<order> &lhs, const std::shared_ptr<order> &rhs) {
                return lhs->price() < rhs->price();
            });
            // matching new order with candidates in order book
            for (std::vector<std::shared_ptr<order>>::iterator k = candidate.begin(); k != candidate.end(); ++k)
            {
                myTrade.push_back(trade(newOrder.name(), (*k)->name(), newOrder.instrument(), std::min(newOrder.quantity(), -1 * (*k)->quantity()), (*k)->price()));
                if (newOrder.quantity() < -1 * (*k)->quantity())
                {
                    (*k)->quantity((*k)->quantity() + newOrder.quantity());
                    newOrder.quantity(0);
		    break;
                }
                else if (newOrder.quantity() > -1 * (*k)->quantity())
                {
                    newOrder.quantity(newOrder.quantity() + (*k)->quantity());
                    (*k)->quantity(0);
                }
                else
                {
                    (*k)->quantity(0);
                    newOrder.quantity(0);
                    break;
                }
            }
            if (newOrder.quantity() != 0) openOrder.push_back(std::make_shared<order>(newOrder));
            candidate.erase(std::remove_if(candidate.begin(),candidate.end(),[](const auto &p){return p->quantity() == 0;}),candidate.end());
        }
    }

    if (newOrder.quantity() < 0) // sell order
    {
        // find buy orders in order book matching instument and acceptable price
        for (std::vector<std::shared_ptr<order>>::iterator j = openOrder.begin(); j != openOrder.end(); ++j)
        {
            if (newOrder.instrument() == (*j)->instrument() && (*j)->quantity() > 0 && (*j)->price() >= newOrder.price())
            {
                candidate.push_back(*j);
            }
        }

        // cannot find matching order, add the new order in order book
        if (candidate.size() == 0)
            openOrder.push_back(std::make_shared<order>(newOrder));
        else
        {
            // sort candidates according to prices
            std::stable_sort(candidate.begin(), candidate.end(), [](const std::shared_ptr<order> &lhs, const std::shared_ptr<order> &rhs) {
                return lhs->price() > rhs->price();
            });
            // matching new order with candidates in order book
            for (std::vector<std::shared_ptr<order>>::iterator k = candidate.begin(); k != candidate.end(); ++k)
            {
                myTrade.push_back(trade((*k)->name(), newOrder.name(), newOrder.instrument(), std::min(-1 * newOrder.quantity(), (*k)->quantity()), (*k)->price()));
                if (-1 * newOrder.quantity() < (*k)->quantity())
                {
                    (*k)->quantity((*k)->quantity() + newOrder.quantity());
                    newOrder.quantity(0);
                    break;
                }
                else if (-1 * newOrder.quantity() > (*k)->quantity())
                {
                    newOrder.quantity(newOrder.quantity() + (*k)->quantity());
                    (*k)->quantity(0);
                }
                else
                {
                    (*k)->quantity(0);
                    newOrder.quantity(0);
                    break;
                }
            }
            if (newOrder.quantity() != 0) openOrder.push_back(std::make_shared<order>(newOrder));
            candidate.erase(std::remove_if(candidate.begin(),candidate.end(),[](const auto &p){return p->quantity() == 0;}),candidate.end());
        }
    }
};
