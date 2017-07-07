#include "order.hpp"
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
    order order2 = order("B","AUDUSD",-100,1.7);
    order order3 = order("C","AUDUSD",100,1.6);
    order order4 = order("D","EURUSD",100,1.7);

    struct orderBookEachMarket
    {
        std::vector<order> ask;
        std::vector<order> bid;
    };

    orderBookEachMarket orderBookEachMarket1;

    orderBookEachMarket1.bid.push_back(order1);
    orderBookEachMarket1.ask.push_back(order2);
    orderBookEachMarket1.bid.push_back(order3);

    std::map<std::string, orderBookEachMarket> orderBook;
    orderBook["AUDUSD"] = orderBookEachMarket1;

    if (orderBook.count(order4.instrument()) == 0)
        order4.quantity() > 0 ? orderBook[order4.instrument()].bid.push_back(order4) : orderBook[order4.instrument()].ask.push_back(order4); 
    else
    {
       if (order4.quantity() > 0)
       {
          if (orderBook[order4.instrument()].ask.empty()) 
              orderBook[order4.instrument()].bid.push_back(order4); 
          else
          {
              while (!orderBook[order4.instrument()].ask.empty())
              {
                   std::vector<order>::iterator it = orderBook[order4.instrument()].ask.begin();
                   if (order4.price() < (*it).price())
                       {
                           orderBook[order4.instrument()].bid.push_back(order4); 
                           break;
                       }
                   else
                   {
                       if (order4.quantity() == std::abs((*it).quantity()))
                       {
                           myTrade.push_back(trade(order4.name(), (*it).name(), order4.instrument(), order4.quantity(), (*it).price()));
                           orderBook[order4.instrument()].ask.erase(it);
                           break;
                       }
                       else if (order4.quantity() < std::abs((*it).quantity()))
                       {
                           (*it).quantity(order4.quantity() + (*it).quantity());
                           break;
                       }
                       else
                       {
                           myTrade.push_back(trade(order4.name(), (*it).name(), order4.instrument(), std::abs((*it).quantity()), (*it).price()));
                           order4.quantity(order4.quantity() + (*it).quantity());
                           orderBook[order4.instrument()].ask.erase(it);
                       }
                   }

              }
              if (order4.quantity() != 0) orderBook[order4.instrument()].bid.push_back(order4);
          }
       }
       else
       {
          if (orderBook[order4.instrument()].ask.empty()) 
              orderBook[order4.instrument()].bid.push_back(order4); 
          else
          {
              while (!orderBook[order4.instrument()].ask.empty())
              {
                   std::vector<order>::iterator it = orderBook[order4.instrument()].ask.begin();
                   if (order4.price() < (*it).price())
                       {
                           orderBook[order4.instrument()].bid.push_back(order4); 
                           break;
                       }
                   else
                   {
                       if (order4.quantity() == std::abs((*it).quantity()))
                       {
                           myTrade.push_back(trade(order4.name(), (*it).name(), order4.instrument(), order4.quantity(), (*it).price()));
                           orderBook[order4.instrument()].ask.erase(it);
                           break;
                       }
                       else if (order4.quantity() < std::abs((*it).quantity()))
                       {
                           (*it).quantity(order4.quantity() + (*it).quantity());
                           break;
                       }
                       else
                       {
                           myTrade.push_back(trade(order4.name(), (*it).name(), order4.instrument(), std::abs((*it).quantity()), (*it).price()));
                           order4.quantity(order4.quantity() + (*it).quantity());
                           orderBook[order4.instrument()].ask.erase(it);
                       }
                   }

              }
              if (order4.quantity() != 0) orderBook[order4.instrument()].bid.push_back(order4);
          }       
       }
    }

    return 0;
}
