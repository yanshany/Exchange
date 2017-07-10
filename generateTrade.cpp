#include "order.hpp"
#include "orderBook.hpp"
#include "trade.hpp"
#include "generateTrade.hpp"
#include <algorithm>
#include <memory>
#include <iostream>
void generateTrade(order& newOrder, std::map<std::string, orderBook>& wholeBook, std::vector<trade>& myTrade)
{
    if (wholeBook.count(newOrder.instrument()) == 0)
        wholeBook[newOrder.instrument()].addAnOrder(newOrder);
    else
    {
       if (newOrder.quantity() > 0)
       {
          if (wholeBook[newOrder.instrument()].ask.empty())
              wholeBook[newOrder.instrument()].addAnOrder(newOrder);
          else
          {
              while (!wholeBook[newOrder.instrument()].ask.empty())
              {
                   std::vector<order>:: iterator it = wholeBook[newOrder.instrument()].ask.begin();
                   if (newOrder.price() < it->price())
                       {
                           wholeBook[newOrder.instrument()].addAnOrder(newOrder);
                           newOrder.quantity(0);
                           break;
                       }
                   else
                   {
                       if (newOrder.quantity() == std::abs(it->quantity()))
                       {
                           myTrade.push_back(trade(newOrder.name(), it->name(), newOrder.instrument(), newOrder.quantity(), it->price()));
                           wholeBook[newOrder.instrument()].ask.erase(it);
                           newOrder.quantity(0);
                           break;
                       }
                       else if (newOrder.quantity() < std::abs(it->quantity()))
                       {
                           myTrade.push_back(trade(newOrder.name(), it->name(), newOrder.instrument(), newOrder.quantity(), it->price()));
                           it->quantity(newOrder.quantity() + it->quantity());
                           newOrder.quantity(0);
                           break;
                       }
                       else
                       {
                           myTrade.push_back(trade(newOrder.name(), it->name(), newOrder.instrument(), std::abs(it->quantity()), it->price()));
                           newOrder.quantity(newOrder.quantity() + it->quantity());
                           wholeBook[newOrder.instrument()].ask.erase(it);
                       }
                   }
                  it++;
              }
              if (newOrder.quantity() != 0) wholeBook[newOrder.instrument()].addAnOrder(newOrder);
          }
       }
       else
       {
          if (wholeBook[newOrder.instrument()].bid.empty())
              wholeBook[newOrder.instrument()].addAnOrder(newOrder);
          else
          {
              while (!wholeBook[newOrder.instrument()].bid.empty())
              {
                   std::vector<order>::iterator it = wholeBook[newOrder.instrument()].bid.begin();
                   if (newOrder.price() > it->price())
                       {
                           wholeBook[newOrder.instrument()].addAnOrder(newOrder);
                           newOrder.quantity(0);
                           break;
                       }
                   else
                   {
                       if (std::abs(newOrder.quantity()) == it->quantity())
                       {
                           myTrade.push_back(trade(it->name(), newOrder.name(), newOrder.instrument(), it->quantity(), it->price()));
                           wholeBook[newOrder.instrument()].bid.erase(it);
                           newOrder.quantity(0);
                           break;
                       }
                       else if (std::abs(newOrder.quantity()) < it->quantity())
                       {
                           myTrade.push_back(trade(it->name(), newOrder.name(), newOrder.instrument(), std::abs(newOrder.quantity()), it->price()));
                           it->quantity(newOrder.quantity() + it->quantity());                           
                           newOrder.quantity(0);
                           break;
                       }
                       else
                       {
                           myTrade.push_back(trade(it->name(), newOrder.name(), newOrder.instrument(), it->quantity(), it->price()));
                           newOrder.quantity(newOrder.quantity() + it->quantity());
                           wholeBook[newOrder.instrument()].bid.erase(it);
                       }
                   }
                  it++;
              }
              if (newOrder.quantity() != 0) wholeBook[newOrder.instrument()].addAnOrder(newOrder);
          }       
       }
    }

};
