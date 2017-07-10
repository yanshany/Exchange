#include "order.hpp"
#include "orderBook.hpp"
#include "trade.hpp"
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>

int main()
{
    std::vector<trade> myTrade;
    order order1 = order("A","AUDUSD",100,1.7);
//    order order2 = order("B","AUDUSD",-100,1.7);
//    order order3 = order("C","AUDUSD",100,1.6);
    order newOrder = order("D","AUDUSD",-100,1.7);

    orderBook orderBookEachMarket = orderBook();

    orderBookEachMarket.addAnOrder(order1);

//    orderBookEachMarket.addAnOrder(order2);
//    orderBookEachMarket.addAnOrder(order3);
    std::cout << orderBookEachMarket;

    std::map<std::string, orderBook> wholeBook;
    wholeBook["AUDUSD"] = orderBookEachMarket;

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

    
    std::cout << wholeBook["AUDUSD"];
    std::cout << myTrade[0];
    return 0;
 
}
